/*
상반기 아이스크림 총주문량이 3,000보다 높으면서 아이스크림의 주 성분이 과일인 아이스크림의 맛을 총주문량이 큰 순서대로 조회하는 SQL 문을 작성해주세요.
*/

-- 코드를 입력하세요
SELECT F.FLAVOR AS FLAVOR
FROM FIRST_HALF AS F
JOIN ICECREAM_INFO AS I
ON F.FLAVOR = I.FLAVOR
WHERE TOTAL_ORDER > 3000
AND INGREDIENT_TYPE = 'fruit_based'
ORDER BY TOTAL_ORDER DESC