import { createSlice, createAsyncThunk } from '@reduxjs/toolkit';
import { apiClient } from '../../utils/requests';
import { create_params } from '../../utils/func';
import { store } from '../store';
import { URL, CmdType, STATE } from '../const';

export const getBuysTable = createAsyncThunk('stateBuys/getBuysTable', async () => {
    const { offset, recordsDisplay } = store.getState().buysReducer;
    const params = create_params(CmdType.table, offset, recordsDisplay);
    const response = await apiClient.post(URL.buy, params);
    return response;
});

export const stateBuys = createSlice({
    name: 'stateBuys',
    initialState: STATE.base,
    reducers: {
        setOffset: (state, action) => {
            state.offset = action.payload.offset;
        },
    },
    extraReducers: builder => {
        builder
            .addCase(getBuysTable.pending, state => {
                state.loading = 'loading';
            })
            .addCase(getBuysTable.fulfilled, (state, action) => {
                state.recordsTotal = action.payload.recordsTotal;
                state.offset = action.payload.offset;
                state.recordsDisplay = action.payload.recordsDisplay;
                state.draw = action.payload.draw;
                state.loading = 'idle';
            })
            .addCase(getBuysTable.rejected, state => {
                state.loading = 'failed';
            });
    },
});

export const { setOffset } = stateBuys.actions;
export const buysReducer = stateBuys.reducer;
