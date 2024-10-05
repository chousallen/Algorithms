#!/bin/bash
make

./execall.sh S IS ALL
./execall.sh C ALL

./execall.sh S QS ALL
./execall.sh C ALL

./execall.sh S RQS ALL
./execall.sh C ALL

./execall.sh S MS ALL
./execall.sh C ALL

./execall.sh S BMS ALL
./execall.sh C ALL