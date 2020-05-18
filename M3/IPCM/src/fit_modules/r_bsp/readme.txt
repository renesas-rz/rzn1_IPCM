r_bsp Package
=============


Overview
--------
The r_bsp package provides a foundation for code to be built on top of. It provides startup code, iodefines, and MCU
information for different boards. There are 2 folders that make up the r_bsp package. The 'mcu' folder contains files 
that are common to a MCU group. These files provide functionality such as easy register access, CPU functions,
and a file named 'mcu_info.h' for each MCU group. The 'mcu_info.h' file has information about the MCU on the board
and is configured based on the information given in r_bsp_config.h. The information in 'mcu_info.h' is used to help 
configure Renesas middleware that uses the r_bsp package. The 'board' folder has a folder with startup code for each 
supported board.  Which MCU and board is chosen is decided by the settings in 'platform.h'. The user can choose which 
board they are using by uncommenting the include path that applies to their board. For example, if you are using the 
RZN1D-DB then you would uncomment the #include "./board/rzn1d-db/r_bsp.h" include path. Users are encouraged to add 
their own boards to the 'board' directory. BSPs are configured by using the r_bsp_config.h file. Each board will have a 
reference configuration file named r_bsp_config_reference.h. The user should copy this file to their project, rename it 
to r_bsp_config.h, and use the options inside the file to configure the BSP for their project.


Features
--------
* Provides SFR access through iodefine.h
* Stores details of MCU in 'mcu_info.h' to help configure Renesas middleware.
* Easily configure BSP through r_bsp_config.h.
* Choose MCU easily by inputting part number details in r_bsp_config.h.
 


File Structure
--------------
r_bsp
|   platform.h 
|   readme.txt
|
+---board                           (Folder for board specific support files)
|   +---rzn1d-db                    (RZ/N1D DB board specific support files)
|   +---rzn1s-db                    (RZ/N1S DB board specific support files)
|   +---rzn1l-db                    (RZ/N1L DB board specific support files)
|   |    :
|   :
|   \---user
|
+---doc
|   +---en
|       xxxxxxx{VERSION_NUMBER}-rzn1.pdf
|   +---ja
|       xxxxxxx{VERSION_NUMBER}-rzn1.pdf
|
\---mcu                             (Folder for MCU specific board support files)
    +---all
    +---rzn1                        (RZ/N1x MCU specific board support files)
    |    :
    :