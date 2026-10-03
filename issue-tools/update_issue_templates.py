#!/usr/bin/env python3
"""Append learning templates to existing issues; preview unless --apply is given."""

import argparse
import json
import re
import runpy
import sys
from datetime import datetime, timezone
from pathlib import Path

import requests


TEMPLATES = {
    "[CS]": "cs.md",
    "[Algorithm]": "problem_solving.md",
    "[Programming]": "programming.md",
    "[Data Structure]": "data_structure.md",
    "[C/Data Structure]": "data_structure.md",
}
MARKER = "<!-- study-archive:learning-template:"


def make_body(title, body, templates):
    """Keep the existing body unchanged and append at most one template."""
    body = body or ""
    for tag, filename in TEMPLATES.items():
        if tag not in title:
            continue
        template = templates[filename]
        headings = re.findall(r"^##\s+.+$", template, flags=re.MULTILINE)
        existing_headings = set(re.findall(r"^##\s+.+$", body, flags=re.MULTILINE))
        if MARKER in body or template in body or all(h in existing_headings for h in headings):
            return None
        separator = "\n\n" if body else ""
        return body + separator + f"{MARKER}{filename} -->\n" + template
    return None


def request_json(session, method, url, **kwargs):
    response = session.request(method, url, timeout=30, **kwargs)
    if not response.ok:
        raise RuntimeError(f"GitHub request failed: HTTP {response.status_code}")
    return response.json(), response


def clean_week_prefix(title, week):
    tag = f"[WEEK{week}]"
    pattern = r"^(?:" + re.escape(tag) + r"[ \t]*){2,}"
    return re.sub(pattern, lambda _: tag + " ", title, count=1)


def main():
    parser = argparse.ArgumentParser(description="기존 이슈에 학습 양식 일괄 추가")
    parser.add_argument("--week", required=True, help="주차 번호 (예: 6)")
    parser.add_argument("--tools-dir", type=Path, default=Path(__file__).resolve().parent)
    parser.add_argument("--fix-week-prefix", action="store_true",
                        help="본문 대신 제목 앞의 중복 WEEK 표시만 정리")
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument("--dry-run", action="store_true", help="미리보기 (기본값)")
    mode.add_argument("--apply", action="store_true", help="기존 이슈 실제 수정")
    args = parser.parse_args()
    if not re.fullmatch(r"\d+(?:-\d+)?", args.week):
        parser.error("--week에는 주차 번호를 입력하세요 (예: 6).")

    tools_dir = args.tools_dir.resolve()
    config = runpy.run_path(str(tools_dir / "secrets.py"))
    token = config["GITHUB_TOKEN"]
    owner, repo = config["REPO_OWNER"], config["REPO_NAME"]
    if not token or token == "your_token_here":
        raise RuntimeError("secrets.py에 GitHub 인증 설정이 필요합니다.")

    templates = {}
    for filename in ([] if args.fix_week_prefix else TEMPLATES.values()):
        path = tools_dir / "templates" / filename
        template = path.read_text(encoding="utf-8").strip()
        if not template or not re.search(r"^##\s+", template, flags=re.MULTILINE):
            raise RuntimeError(f"양식이 비어 있거나 제목이 없습니다: {filename}")
        templates[filename] = template

    session = requests.Session()
    session.headers.update({
        "Authorization": f"Bearer {token}",
        "Accept": "application/vnd.github+json",
        "X-GitHub-Api-Version": "2026-03-10",
    })
    base_url = f"https://api.github.com/repos/{owner}/{repo}/issues"
    week_pattern = re.compile(r"\[WEEK" + re.escape(args.week) + r"(?:\]|-\d{1,2}/)")
    url = base_url
    params = {"state": "all", "per_page": 100, "sort": "created", "direction": "asc"}
    changes = []
    while url:
        issues, response = request_json(session, "GET", url, params=params)
        for issue in issues:
            if "pull_request" in issue or not week_pattern.search(issue["title"]):
                continue
            field = "title" if args.fix_week_prefix else "body"
            old_value = issue.get(field) or ""
            new_value = (clean_week_prefix(issue["title"], args.week)
                         if args.fix_week_prefix
                         else make_body(issue["title"], issue.get("body"), templates))
            if new_value is not None and new_value != old_value:
                changes.append({
                    "number": issue["number"], "title": issue["title"],
                    "field": field, "old_value": old_value, "new_value": new_value,
                })
        url = response.links.get("next", {}).get("url")
        params = None

    print(f"대상: {owner}/{repo} / WEEK{args.week}")
    operation = "제목을 정리할" if args.fix_week_prefix else "양식을 추가할"
    print(f"{operation} 이슈: {len(changes)}개")
    for change in changes:
        print(f"\n#{change['number']} {change['title']}")
        print("변경 후: " + change["new_value"] if args.fix_week_prefix else change["new_value"])
    if not args.apply:
        print("\n미리보기 완료. GitHub 이슈는 수정하지 않았습니다.")
        return
    if not changes:
        return

    backup_dir = tools_dir / "template-update-backups"
    backup_dir.mkdir(exist_ok=True)
    timestamp = datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%S%fZ")
    backup = backup_dir / f"week{args.week}-{timestamp}.json"
    backup.write_text(json.dumps({"repository": f"{owner}/{repo}", "changes": changes},
                                 ensure_ascii=False, indent=2), encoding="utf-8")
    print(f"\n수정 전 내용 백업: {backup}")
    for change in changes:
        issue_url = f"{base_url}/{change['number']}"
        current, _ = request_json(session, "GET", issue_url)
        field = change["field"]
        if (current.get(field) or "") != change["old_value"]:
            raise RuntimeError(f"#{change['number']} 내용이 조회 후 변경돼 중단했습니다. 다시 미리보세요.")
        request_json(session, "PATCH", issue_url, json={field: change["new_value"]})
        verified, _ = request_json(session, "GET", issue_url)
        if (verified.get(field) or "") != change["new_value"]:
            raise RuntimeError(f"#{change['number']} 수정 후 내용 확인에 실패했습니다.")
        print(f"수정 및 확인 완료: #{change['number']}")


if __name__ == "__main__":
    try:
        main()
    except (OSError, KeyError, RuntimeError, requests.RequestException) as error:
        print(f"오류: {error}", file=sys.stderr)
        sys.exit(1)
