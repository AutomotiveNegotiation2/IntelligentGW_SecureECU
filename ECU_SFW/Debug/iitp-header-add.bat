::***************************************************************************
:: iitp-header add
::***************************************************************************
FOR %%I in (MCUXpresso_IDE_FW.bin) do set /A img_sz=%%~zI
echo %img_sz%
>hdr_0.bin echo %img_sz%

FOR %%I in (hdr_0.bin) do set /A img_sz_str_len=%%~zI
echo %img_sz_str_len%
set /a hdr_img_sz_pad_len=0x80 - %img_sz_str_len%
srec_cat hdr_0.bin -Binary -fill 0xFF %img_sz_str_len% 0x80 -o image_size.bin -Binary

>hdr_1.bin echo 1.5.0

FOR %%I in (hdr_1.bin) do set /A version_str_len=%%~zI
echo %version_str_len%
set /a hdr_version_pad_len=0x80 - %version_str_len%
srec_cat hdr_1.bin -Binary -fill 0xFF %version_str_len% 0x80 -o sign.bin -Binary

copy /B image_size.bin+sign.bin hdr_2.bin

openssl dgst -sign  private.pem -keyform PEM -sha256 -out img.sign -binary MCUXpresso_IDE_FW.bin

copy /B hdr_2.bin+img.sign hdr_3.bin
srec_cat hdr_3.bin -Binary -fill 0xFF 0x0200 0x1000 -o hdr_4.bin -Binary

copy /B hdr_4.bin+MCUXpresso_IDE_FW.bin fw_plus_iitp_hdr.bin

