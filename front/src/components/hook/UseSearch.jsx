import { useState } from 'react';

export const UseSearchForm = () => {
    const [formData, setForm] = useState({});

    const handleInputChange = (e) => {
        const { name, value } = e.target;
        setForm(prev => ({ ...prev, [name]: value }));
    };

    // Для полей, которые передают значение напрямую (не событие)
    const setField = (name, value) => {
        setForm(prev => ({ ...prev, [name]: value }));
    };

    // Специальный обработчик для диапазона дат
    const handleDateRange = (dates) => {
        const [start, end] = dates || [null, null];
        setForm(prev => ({ ...prev, startDate: start, endDate: end }));
    };

    return {
        formData,
        setForm,
        handleInputChange,
        setField,
        handleDateRange,
    };
};
