import time
import logging
from functools import wraps
from libs.str.base import random_string
from typing import Callable, Concatenate
from libs.types.exp import R, P

logger = logging.getLogger(__name__)

def calculate_running_time(func: Callable[Concatenate[str, P], R]) -> Callable[P, R]:  # type: ignore
    @wraps(func)
    def wrapper(*args: P.args, **kwargs: P.kwargs) -> R:
        begin = time.time()
        random_name = random_string(5).lower()
        
        result = func(random_name, *args, **kwargs)
        
        end = time.time()
        elapsed = end - begin
        
        elapsed_min = int(elapsed // 60)
        elapsed_sec = int(elapsed % 60)
        
        logger.info(f"{random_name} Время выполнения {func.__name__} {elapsed_min} минут {elapsed_sec} секунд.")
        
        return result
    return wrapper

def calculate_float_time(func: Callable[P, None]) -> Callable[P, float]:  # type: ignore
    @wraps(func)
    def wrapper(*args: P.args, **kwargs: P.kwargs) -> float:

        begin = time.time()
        func(*args, **kwargs)
        end = time.time()

        elapsed = end - begin
        return elapsed

    return wrapper
