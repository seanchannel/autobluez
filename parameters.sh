
## Defaults for test environment

export EL_fw_env=${env:-qa}
export EL_fw_index=${index:-universal}
export EL_fw_version=${version:-v12}
export EL_fw_bleversion=${bleversion:-15}
export EL_fw_wifiversion=${wifiversion:-1.0.0}
export EL_ssid=${ssid:-WG2}
export EL_pswd=${pswd:-clearwater}
export EL_ssid_len=`echo -n $EL_ssid | wc -c`
export EL_pswd_len=`echo -n $EL_pswd | wc -c`

export EL_gallons=${gal:-1000}
export EL_fc_target=${fc_target:-3}
export EL_fc_limit=${fc_limit:-1}
export EL_ph_target=${ph:-7.5}
export EL_flow_delta=${delta:-9.0}
export EL_meas_hr=${meas_hr:-10}
export EL_meas_min=${meas_min:-11}
export EL_pod_meas_hr=`expr $EL_meas_hr - 7`

# variables for Manufacturing and diagnostic tests
export EL_idleCurrent_min=${idleCurrent_min:-0}
export EL_idleCurrent_max=${idleCurrent_max:-0.0004}
export EL_BLECurrent_min=${BLECurrent_min:-0}
export EL_BLECurrent_max=${BLECurrent_max:-0.03}
export EL_tempCurrent_min=${tempCurrent_min:-0.003}
export EL_tempCurrent_max=${tempCurrent_max:-0.05}
export EL_versionCurrent_min=${versionCurrent_min:-0.03}
export EL_versionCurrent_max=${versionCurrent_max:-0.09}
export EL_padMotorCurrent_min=${padMotorCurrent_min:-0.1}
export EL_padMotorCurrent_max=${padMotorCurrent_max:-0.5}
export EL_padMotoSamples_min=${padMotorSamples_min:-60}
export EL_RGBCurrent_min=${RGBCurrent_min:-0.01}
export EL_RGBCurrent_max=${RGBCurrent_max:-0.03}

# test runtime configuration
export EL_timeout=${timeout:-30}
export EL_DELAY_WAIT_FOR_HOST=${EL_DELAY_WAIT_FOR_HOST:-5000}
export EL_SCREENRC=screenrc
export EL_SHELL=`which dash`
export PATH=./tests:/usr/local/bin:/usr/local/sbin:/opt/local/bin:/opt/local/sbin:/usr/bin:/bin:/usr/sbin:/sbin:/bin
export TERM=${term:-screen}
export EL_serial=${serial:-NONE}
export EL_power=${power:-NONE}
export EL_power_rate=${power_rate:-1.2}
export EL_handle=${handle:-0x0010}
