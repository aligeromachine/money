import re
from typing import Any

class SQLInjectionDetector:
    """Класс для обнаружения SQL-инъекций"""
    # Опасные паттерны SQL инъекций
    SQL_PATTERNS = [
        r"(\bSELECT\b.*\bFROM\b.*\bWHERE\b)",
        r"(\bINSERT\b.*\bINTO\b)",
        r"(\bUPDATE\b.*\bSET\b)",
        r"(\bDELETE\b.*\bFROM\b)",
        r"(\bDROP\b.*\bTABLE\b)",
        r"(\bUNION\b.*\bSELECT\b)",
        r"(\bOR\b.*\b1\s*=\s*1\b)",
        r"(\bAND\b.*\b1\s*=\s*1\b)",
        r"(--)",
        r"(;.*--)",
        r"(\bEXEC\b.*\bXP_\w+\b)",
        r"(\bINTO\s+OUTFILE\b)",
        r"(\bLOAD_FILE\()",
        r"(\bSLEEP\()",
        r"(\bBENCHMARK\()",
        r"('.*\bOR\b.*'.*=.*')",
        r"(\|\|.*\bOR\b)",
        r"(/\*.*\*/)",
    ]

    @classmethod
    def check_sql_injection(cls, value: Any) -> bool:
        if not isinstance(value, str):
            return False

        value_upper = value.upper()
        for pattern in cls.SQL_PATTERNS:
            if re.search(pattern, value_upper, re.IGNORECASE):
                return True
        return False

    @classmethod
    def sanitize_params(cls, param: str | None) -> str | None:
        if not param:
            return None
        if cls.check_sql_injection(param):
            return re.sub(r"['\";\\-]", '', param)

        return param
