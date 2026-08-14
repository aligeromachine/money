class CONST:
    POST: str = 'POST'
    GET: str = 'GET'
    PUT: str = 'PUT'
    empty: str = ''
    emptyb: bytes = b''
    FormatT: str = '%d-%m-%Y %H:%M:%S'
    FormatDDP: str = '%Y-%m-%d %H:%M:%S'
    FormatFull: str = '%Y-%m-%dT%H:%M:%S.%fZ'
    FormatJS: str = "%a %b %d %Y %H:%M:%S"
    FormatAccess: str = '%m/%d/%y %H:%M:%S'
    DtRaw: str = '%Y-%m-%d %H:%M:%S.%fz'
    FormatF: str = '%d-%m-%Y_%H-%M-%S'
    FTime: str = '%H:%M:%S'
    FDate: str = '%Y-%m-%d'
    FMonth: str = '%Y-%m'
    csrftoken: str = 'csrfmiddlewaretoken'
    timeout: int = 10
    localhost: str = '127.0.0.1'
    UTF8: str = 'utf-8'
    ASCII: str = 'ascii'
    session_null: bytes = b'\x00\x00\x00\x00'
    zero: str = '0'
    DAY_BEGIN: str = '00:00:00'
    DAY_END: str = '23:59:59'
    CHUNK_SIZE: int = 100
    data: str = 'data'
    raw: str = 'raw'


MAX_TRY_COUNT: int = 5
PARTS_SIZE: int = 1_024 * 250
