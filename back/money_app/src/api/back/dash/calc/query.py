SQL_ORDER_CARDS: str = """
SELECT 
    card.id, 
    card.title, 
    card.amount
FROM 
    content.cards card
WHERE 
    card.user_id = %s
ORDER BY 
    card.checked desc, 
    card.amount desc
LIMIT 3
"""
CALC_BUY_TOTAL = """
SELECT
    buy.id,
    buy.created::date base_dt,
    buy.title,
    buy.amount,
    shop.title shop,
    cat.title cat,
    prod.title prod
FROM
    content.buy buy
JOIN
    content.shop shop on buy.shop_id = shop.id
JOIN
    content.products prod on buy.products_id = prod.id
JOIN
    content.catalog cat on prod.catalog_id = cat.id
WHERE 
    EXTRACT(YEAR FROM buy.created) = EXTRACT(YEAR FROM CURRENT_DATE)
AND 
    buy.user_id = %s
"""

CALC_PROF_TOTAL = """
SELECT
    prof.id,
    prof.created::date base_dt,
    prof.title,
    prof.amount,
    src.title source
FROM
    content.profit prof
JOIN
    content.source src on src.id = prof.source_id
WHERE 
    EXTRACT(YEAR FROM prof.created) = EXTRACT(YEAR FROM CURRENT_DATE)
AND 
    prof.user_id = %s
"""
