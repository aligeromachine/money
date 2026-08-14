SQL_SEARCH = """
SELECT
    buy.id,
    buy.created,
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
"""
