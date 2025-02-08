/*
DEVELOPER_INFOS 테이블에서 Python 스킬을 가진 개발자의 정보를 조회하려 합니다. Python 스킬을 가진 개발자의 ID, 이메일, 이름, 성을 조회하는 SQL 문을 작성해 주세요.

결과는 ID를 기준으로 오름차순 정렬해 주세요.
*/

-- 코드를 작성해주세요
SELECT ID, EMAIL, FIRST_NAME, LAST_NAME
FROM DEVELOPER_INFOS
WHERE SKILL_1 = 'Python'
OR SKILL_2 = 'Python'
OR SKILL_3 = 'Python'
ORDER BY ID ASC