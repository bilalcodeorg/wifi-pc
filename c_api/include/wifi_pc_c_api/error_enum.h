#pragma once

// Enums must be added from end and must have prefix of kWpcError

typedef enum {
    kWpcErrorNotPresent,
    kWpcErrorGeneral,
    kWpcErrorOs,
    kWpcErrorNoAdapter
} WpcErrorCode;