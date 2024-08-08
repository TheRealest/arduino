#ifndef DATA_STATE_H_
#define DATA_STATE_H_

struct RowState {
  uint8_t values[6];
};

struct DataState {
  RowState rows[8];
};

#endif
