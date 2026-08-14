from django.http import HttpRequest
import logging
from api.back.decore import validate_model
from api.back.catalog.table import table_cat_data
from api.back.catalog.base import add_cat_data, delete_cat_row, edit_cat_data, get_cat_row, list_cat_data
from api.back.catalog.model import CatalogMessage
from api.back.const import CmdRouter

logger = logging.getLogger(__name__)

@validate_model(CatalogMessage)  # type: ignore
def invoke_response(request: HttpRequest, item: CatalogMessage) -> dict | list:
    respo = dict(data="err", message="undefinded")

    if item.command == CmdRouter.table:
        respo = table_cat_data(item=item)

    if item.command == CmdRouter.add:
        respo = add_cat_data(item=item)

    if item.command == CmdRouter.edit:
        respo = edit_cat_data(item=item)

    if item.command == CmdRouter.delete:
        respo = delete_cat_row(item=item)

    if item.command == CmdRouter.row:
        respo = get_cat_row(item=item)

    if item.command == CmdRouter.listkeys:
        respo = list_cat_data(item=item)

    return respo
