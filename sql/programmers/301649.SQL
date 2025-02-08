/*
대장균 개체의 크기를 내름차순으로 정렬했을 때 상위 0% ~ 25% 를 'CRITICAL', 26% ~ 50% 를 'HIGH', 51% ~ 75% 를 'MEDIUM', 76% ~ 100% 를 'LOW' 라고 분류합니다. 대장균 개체의 ID(ID) 와 분류된 이름(COLONY_NAME)을 출력하는 SQL 문을 작성해주세요. 이때 결과는 개체의 ID 에 대해 오름차순 정렬해주세요 . 단, 총 데이터의 수는 4의 배수이며 같은 사이즈의 대장균 개체가 서로 다른 이름으로 분류되는 경우는 없습니다.
*/

-- 코드를 작성해주세요
SELECT *
FROM (
    SELECT D.ID, IF((@SEQ := @SEQ+1) / LENGTH*100 <= 25, 'CRITICAL', 
            IF(@SEQ / LENGTH * 100 <= 50, 'HIGH', 
            IF(@SEQ / LENGTH * 100 <= 75, 'MEDIUM', 'LOW'))) AS COLONY_NAME
    FROM ECOLI_DATA AS D, (SELECT @SEQ := 0) A, (SELECT COUNT(*) AS LENGTH FROM ECOLI_DATA) AS C
    ORDER BY SIZE_OF_COLONY DESC
) AS DATAS
ORDER BY ID ASC