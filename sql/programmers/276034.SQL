/*
DEVELOPERS 테이블에서 Python이나 C# 스킬을 가진 개발자의 정보를 조회하려 합니다. 조건에 맞는 개발자의 ID, 이메일, 이름, 성을 조회하는 SQL 문을 작성해 주세요.

결과는 ID를 기준으로 오름차순 정렬해 주세요.
*/

-- 코드를 작성해주세요
SELECT DISTINCT D.ID, D.EMAIL, D.FIRST_NAME, D.LAST_NAME
FROM DEVELOPERS AS D
JOIN SKILLCODES AS S
ON S.CODE & D.SKILL_CODE != 0
WHERE S.NAME IN ('Python', 'C#')
ORDER BY D.ID ASC
