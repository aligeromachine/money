import { postRequestCheck } from '../../utils/requests';
import { URL, CmdType } from '../const';

export const getShopOptions = async () => {
    const params = {
        command: CmdType.listkeys,
    };
    const response = await postRequestCheck(URL.shop, params);
    if (!response) return Promise.reject('Error response');
    return response;
};
