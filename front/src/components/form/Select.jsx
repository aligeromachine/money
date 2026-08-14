import React from 'react';
import { useState, useEffect } from 'react';
import { CFormSelect } from '@coreui/react';

export const AsyncFormSelect = ({ label, onChange, value, name, request }) => {
    const [options, setOptions] = useState([]);

    useEffect(() => {
        const fetchOptions = async () => {
            const response = await request();
            const reaponseOptions = response.map(item => ({
                value: String(item.id),
                label: item.title,
            }));
            
            setOptions([{ value: '', label: '-- Выберите --', disabled: true }, ...reaponseOptions]);

            if (reaponseOptions.length > 0) {
                // Создаем "симулированное" событие, чтобы родитель не падал
                const syntheticEvent = {
                    target: {
                        value: reaponseOptions[0].value,
                        name: name,
                    }
                };
                onChange(syntheticEvent);
            }
        };
        fetchOptions();
    }, []);

    return <CFormSelect label={label} value={value} name={name} onChange={onChange} options={options} placeholder="Выберите вариант..." />;
};
