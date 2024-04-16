if [[ -f /opt/vision_apps/test_data/psdkra/app_multi_cam_codec/TI_Custom_1920x1080_5secs.264 ]]
then
    cp /opt/vision_apps/test_data/psdkra/app_multi_cam_codec/TI_Custom_1920x1080_5secs.264 /tmp/test_data.264
else
    echo "ERROR=> Test Data Not Found"
    exit -1
fi

/opt/vision_apps/vx_app_multi_cam_codec.out --cfg /opt/vision_apps/app_multi_cam_codec.cfg

if [[ -s /tmp/output_video_0.264 ]]
then
    mv /tmp/output_video_0.264 /ti_fs/vision_apps/
fi

if [[ -s /tmp/output_video_1.264 ]]
then
    mv /tmp/output_video_1.264 /ti_fs/vision_apps/
fi

if [[ -s /tmp/output_video_2.264 ]]
then
    mv /tmp/output_video_2.264 /ti_fs/vision_apps/
fi

if [[ -s /tmp/output_video_3.264 ]]
then
    mv /tmp/output_video_3.264 /ti_fs/vision_apps/
fi

if [[ -f /tmp/test_data.264 ]]
then
    rm /tmp/test_data.264
fi
