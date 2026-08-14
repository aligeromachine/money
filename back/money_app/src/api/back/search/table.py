from decimal import Decimal
import logging
from money.models import Buy
from libs.django.base import count_raw_sql
from api.back.search.model import SearcSelector, SearchMessage, SearchParams
from api.back.search.query import SQL_SEARCH

logger = logging.getLogger(__name__)

def table_search_data(item: SearchMessage) -> dict:

    if isinstance(item.form_data, SearchParams):
        elem: SearchParams = item.form_data

        conditions = []
        params = []

        conditions.append("buy.user_id = %s")
        params.append(item.user_id)

        if elem.startDate and elem.endDate:
            conditions.append("buy.created::date >= %s::date AND buy.created <= %s::date")
            params.append(elem.startDate)
            params.append(elem.endDate)
        else:
            if elem.startDate:
                conditions.append("buy.created::date = %s::date")
                params.append(elem.startDate)

        if isinstance(elem.groupTypeProd, list) and elem.groupTypeProd:
            quote = '%s,' * len(elem.groupTypeProd)
            conditions.append(f"prod.catalog_id in ({quote[:-1]})")
            params.extend([it.value for it in elem.groupTypeProd])

        if isinstance(elem.groupOrganization, list) and elem.groupOrganization:
            quote = '%s,' * len(elem.groupOrganization)
            conditions.append(f"buy.shop_id in ({quote[:-1]})")
            params.extend([it.value for it in elem.groupOrganization])

        if elem.prim:
            conditions.append("buy.title ILIKE %s")
            params.append(f'%{elem.prim}%')

        where_clause = " AND ".join(conditions)
        query = SQL_SEARCH
        if where_clause:
            query += f" WHERE {where_clause} \n"

        query_count = f"select 1 id, count(1) c from ({query})"

        query += "ORDER BY \n"
        query += "buy.created desc \n"
        records = [SearcSelector.from_orm(it) for it in Buy.objects.raw(raw_query=query, params=params)]

        ls = records[item.offset * item.limit:item.limit]

        count = count_raw_sql(model=Buy, sql=query_count, params=params)

        unique_shops = len({r.shop for r in records})
        unique_prods = len({r.prod for r in records})
        total_amount = sum([r.amount for r in records], Decimal(0))
        total_dates = set(r.base_dt for r in records)
        days_count = len(total_dates)
        range_days = 0

        if total_dates:
            min_date = min(total_dates)
            max_date = max(total_dates)
            range_days = (max_date - min_date).days + 1

        stat = dict(
            sum=total_amount,
            day=f'{range_days}/{days_count}',
            org=unique_shops,
            prod=unique_prods,
            rng=f'{min_date}/{max_date}'
        )

        table = dict(
            recordsTotal=count,
            offset=item.offset,
            recordsDisplay=item.limit,
            draw=[it.model_dump() for it in ls]
        )

        return dict(stat=stat, table=table)

    return dict(stat={}, table={})
