rzn1_dma_mux
=============


Overview
--------
The rzn1_dma_mux header defines the hardware DMA multiplexed sources as outlined in <CFG_DMAMUX — DMA1 & DMA2 Multiplexer 
Register> in the hardware manual (indicating the corresponding DMA controller, source request line and its multiplexing value).
The DMA_MUX_CONFIG array replicates this register. It is important that the ordering remains as is.
Should the multiplexing be desired to be altered, the alternative request options for each array element are shown in comments. 
