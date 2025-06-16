【ISP 效果配置方法   编译效果.h】
1) （以 GC2053 为例）在工具中将.dat 文件转换为.h 文件，拷贝至 SDK；
文件目录：external/eyesee-mpp/middleware/sun8iw21/media/LIBRARY/libisp/isp_cfg/SENSOR_H/gc2053/
2) 将效果.h 包含至 isp_ini_parse.c
文件目录：external/eyesee-mpp/middleware/sun8iw21/media/LIBRARY/libisp/isp_cfg/isp_ini_parse.c

根据使用场景注册 struct isp_cfg_array cfg_arr[] 结构体，参数含义如下：
① Sensor 模块名称：sensor_mipi
② ISP 效果头文件名称，建议按照版本填写，便于区分和检查
③ 分辨率宽度
④ 分辨率高度
⑤ 帧率
⑥ 红外 IR 模式标志位：标志这份效果为红外夜视黑白效果
⑦ WDR 模式标志位：标志这份效果为 WDR 模式专用效果，使用 WDR 模式才需要配置
⑧ ISP 效果.h 末尾的 ISP 参数结构体“struct isp_cfg_pt gc2053_mipi_v821_isp_cfg”

【ISP 效果配置使用方式 效果.bin】
使用TigerISP工具，将.dat转换成.bin文件，打包到文件系统，
在应用中通过调用AW_MPI_ISP_ReadIspCfgBin函数进行效果配置。