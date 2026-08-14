import { useState, useEffect } from 'react';
import Select from 'react-select';
import { CCard, CCardBody, CCol, CRow, CCardHeader, CButton, CFormInput, CInputGroup, CInputGroupText } from '@coreui/react';
import { Auth } from '../../components/auth/Auth';
import { BlueStrip, RedStrip } from '../../components/elems/LineStrip';
import { RangeDatePicker } from '../../components/datetimepiker/BigDatepicker';
import { UseSearchForm } from '../../components/hook/UseSearch';
import { getSearchOptions } from '../../services/search/query';
import { getSearchTable } from '../../services/search/request';
import { SearchProvider } from '../../components/hook/SearchContext';
import { TableSearch } from './content/Table';
import { dateUtils } from '../../utils/func';
import styles from './Search.module.css';
import { ItogSum } from './content/Itog'
import { DEFAULT_SUM, DEFAULT_GROUP, DEFAULT_GRIG } from './content/const'
import { SearchModal } from './content/modal/Base';
import { isEmpty } from '../../utils/func';

export const Search = () => {
    const { formData, setForm, setField, handleInputChange, handleDateRange } = UseSearchForm();
    const [dataSum, setSum] = useState(DEFAULT_SUM);
    const [options, setOptions] = useState(DEFAULT_GROUP);
    const [dataTable, setTable] = useState(DEFAULT_GRIG);

    useEffect(() => {
        const fetchOptions = async () => {
            const data = await getSearchOptions();
            setOptions(data);
        };
        fetchOptions();
    }, []);
    
    const clearSearch = async () => {
        setSum(DEFAULT_SUM);
        setOptions(DEFAULT_GROUP);
        setForm({});
        setTable(DEFAULT_GRIG);
        setOptions(await getSearchOptions());
    };

    const requestSearch = async () => {
        const raw = formData;
        Object.keys(raw).forEach(key => {
            if (raw[key] instanceof Date) {
                raw[key] = dateUtils.toReduxFormat(raw[key]);
            }
        });
        if (isEmpty(raw)) return;
        const response = await getSearchTable(dataTable.offset, dataTable.recordsDisplay, raw);
        setTable(response.table);
        setSum(response.stat);
    };

    async function onOffset(value) {
        console.log(value);
    }

    return (
        <Auth>
            <CCard className="mb-4">
                <CCardHeader>
                    <strong>Поиск</strong>
                </CCardHeader>
                
                <CCardBody className={styles.bgcGray}>
    
                    <CInputGroup className="mb-3">
                        <CInputGroupText>Диапазон</CInputGroupText>
                        <CCol xs={3}>
                            <RangeDatePicker startDate={formData.startDate} endDate={formData.endDate} onChange={handleDateRange} />
                        </CCol>

                        <CInputGroupText>Тип Продукта</CInputGroupText>
                        <CCol>
                            <Select
                                options={options.groupTypeProd}
                                value={formData.groupTypeProd || []}
                                onChange={v => setField('groupTypeProd', v)}
                                placeholder={'Выберите типы...'}
                                isMulti
                                className="basic-multi-select"
                                classNamePrefix="select"
                            />
                        </CCol>
                    </CInputGroup>

                    <CInputGroup className="mb-3">
                        <CInputGroupText>Магазин</CInputGroupText>
                        <CCol>
                            <Select
                                options={options.groupOrganization}
                                value={formData.groupOrganization || []}
                                onChange={v => setField('groupOrganization', v)}
                                placeholder={'Выберите типы...'}
                                isMulti
                                className="basic-multi-select"
                                classNamePrefix="select"
                            />
                        </CCol>
                        <CInputGroupText>Примечание</CInputGroupText>
                        <CFormInput name='prim' value={formData.prim || ''} onChange={handleInputChange} placeholder="Помидоры"/>
                    </CInputGroup>

                    <div className={styles.buttonWrapper}>
                        <CButton color="secondary" onClick={requestSearch} style={{ width: '150px' }}>
                            Найти
                        </CButton>
                        <CButton color="primary" onClick={clearSearch} style={{ width: '150px' }}>
                            Очистить
                        </CButton>
                    </div>

                </CCardBody>

                <BlueStrip />

                <ItogSum data={dataSum} />

                <RedStrip/>

                <CCardBody>
                    <SearchProvider>
                        <SearchModal />
                        <TableSearch st={dataTable} />
                    </SearchProvider>
                </CCardBody>

            </CCard>
        </Auth>
    );
};
