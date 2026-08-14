import { CCardBody, CCol, CRow, CWidgetStatsB } from '@coreui/react';

export const ItogSum = ({data}) => {
    return (
        <CCardBody>
            <CRow xs={{ gutter: 4 }}>
                <CCol xs={12} sm={6} xl={4} xxl={3}>
                    <CWidgetStatsB
                        progress={{ color: 'success', value: 89.9 }}
                        text=""
                        title="Сумма"
                        value={`${data.sum}`}
                    />
                </CCol>
                <CCol xs={12} sm={6} xl={4} xxl={3}>
                    <CWidgetStatsB
                        value={`${data.day}`}
                        title={data.rng}
                        progress={{ color: 'info', value: 89.9 }}
                        text=""
                    />
                </CCol>
                <CCol xs={12} sm={6} xl={4} xxl={3}>
                    <CWidgetStatsB
                        value={`${data.org}`}
                        title="Магазины"
                        progress={{ color: 'warning', value: 89.9 }}
                        text=""
                    />
                </CCol>
                <CCol xs={12} sm={6} xl={4} xxl={3}>
                    <CWidgetStatsB
                        value={`${data.prod}`}
                        title="Продукты"
                        progress={{ color: 'primary', value: 89.9 }}
                        text=""
                    />
                </CCol>
            </CRow>            
        </CCardBody>
    );
};
