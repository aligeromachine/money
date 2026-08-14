import { apiClient } from '../../utils/requests';
import { URL } from '../const';
import { ALL } from './const';

export const getLogger = async () => {
    const response = await apiClient.post(URL.log, { command: ALL });
    if (!response) return Promise.reject('Error response');
    return response;
};

export const delLogger = async msg => {
    const response = await apiClient.post(URL.log, {
        command: `delete_${msg}`,
    });
    if (!response) return Promise.reject('Error response');
    return response;
};
