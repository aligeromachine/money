import logging
import re
import time
import subprocess
from multiprocessing import Process
from typing import Callable
from src.libs.decore.calc_time import calculate_float_time
from src.libs.const import CONST

logger = logging.getLogger(__name__)

def SimpleProccess(func: Callable, arg: tuple) -> None:
    p = Process(target=func, args=arg)
    p.start()

def get_ip_address_subprocess() -> str:
    try:
        respo_addr: str = CONST.empty
        list_face = ['eth1']
        for it in list_face:
            match = re.search(r'(\d+\.\d+\.\d+\.\d+)', run_bash_out(f'ip addr show {it}'))
            if match:
                respo_addr = str(match.group(1)).strip()
                break

        if not respo_addr:
            matchs = re.finditer(r'(\d+\.\d+\.\d+\.\d+)/(16|24)', run_bash_out('ip addr show'))

            if matchs:
                matchs_sort = sorted(matchs, key=lambda x: int(x.group(2)))
                for itx in matchs_sort:
                    if int(itx.group(2)) == 16:
                        respo_addr = str(itx.group(1)).strip()
                        break
                    respo_addr = str(itx.group(1)).strip()

        if not respo_addr:
            return CONST.localhost

        return respo_addr
    except subprocess.CalledProcessError:
        return CONST.localhost

def run_bash_out(cmd: str) -> str:

    result: str = ''

    try:
        with subprocess.Popen(args=cmd, stdout=subprocess.PIPE, text=True, encoding='utf-8', shell=True) as p:
            if not p or not p.stdout:
                return result

            for line in iter(p.stdout.readline, ''):
                result += line.strip()

    except Exception as ex:
        logger.error(str(ex))

    return result

def run_bash_out_trace(cmd: str, lp: bool = False, debug: bool = False) -> str:

    if debug:
        logger.info(cmd)
        time.sleep(CONST.timeout)
        return str(CONST.empty)

    if lp:
        logger.info(cmd)

    return run_bash_out(cmd=cmd)

def run_bash(cmd: str) -> int:

    returned_value = 1

    try:
        returned_value = subprocess.call(cmd, stdin=None, stdout=None, stderr=None, shell=True)
    except Exception as ex:
        logger.error(str(ex))

    return returned_value


@calculate_float_time  # type: ignore
def run_bash_trace(cmd: str, lp: bool = False, debug: bool = False) -> None:

    if debug:
        logger.info(f'COPY dubug {cmd}')
        time.sleep(CONST.timeout)
        return

    if lp:
        logger.info(f'🚀 Старт выполнения: {cmd}')

    returned_value = run_bash(cmd=cmd)

    if lp:
        logger.info(f"✅ Завершён. Код: {cmd} / {returned_value}")
