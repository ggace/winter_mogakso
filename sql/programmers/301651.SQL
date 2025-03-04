/*
각 세대별 자식이 없는 개체의 수(COUNT)와 세대(GENERATION)를 출력하는 SQL문을 작성해주세요. 이때 결과는 세대에 대해 오름차순 정렬해주세요. 단, 모든 세대에는 자식이 없는 개체가 적어도 1개체는 존재합니다.
*/

-- 코드를 작성해주세요
WITH RECURSIVE TREE(ID, PARENT, GENERATION) AS (
    SELECT ID, PARENT_ID, 1
    FROM ECOLI_DATA
    WHERE PARENT_ID IS NULL
    
    UNION ALL
    
    SELECT ECOLI_DATA.ID, ECOLI_DATA.PARENT_ID, GENERATION+1
    FROM ECOLI_DATA
    JOIN TREE
    WHERE ECOLI_DATA.PARENT_ID = TREE.ID
)

SELECT COUNT(*) AS COUNT, T.GENERATION AS GENERATION
FROM TREE AS T
WHERE (
    SELECT COUNT(*) AS C
    FROM ECOLI_DATA AS D
    WHERE T.ID = D.PARENT_ID
) = 0
GROUP BY T.GENERATION
ORDER BY GENERATION