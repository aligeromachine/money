import { apiClient } from '../../utils/requests';
import { URL, CmdType } from '../const';

export const getDash = async () => {
    const response = await apiClient.post(URL.dash, { command: CmdType.info });
    if (!response) return Promise.reject('Error response');
    return response;
};
