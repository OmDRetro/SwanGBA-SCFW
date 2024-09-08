#include <gba.h>
#include <string.h>

#include "WonderSwan.h"
#include "WSBorder.h"
#include "WSCBorder.h"
#include "PCV2Border.h"
#include "Gui.h"
#include "Cart.h"
#include "Gfx.h"
#include "ARMV30MZ/ARMV30MZ.h"


int packState(void *statePtr) {
	int size = 0;
	memcpy(statePtr+size, wsRAM, sizeof(wsRAM));
	size += sizeof(wsRAM);
	size += sphinxSaveState(statePtr+size, &sphinx0);
	size += V30SaveState(statePtr+size, &V30OpTable);
	memcpy(statePtr+size, wsSRAM, sizeof(wsSRAM));
	size += sizeof(wsSRAM);
	size += wsEepromSaveState(statePtr+size, &extEeprom);
	return size;
}

void unpackState(const void *statePtr) {
	int size = 0;
	memcpy(wsRAM, statePtr+size, sizeof(wsRAM));
	size += sizeof(wsRAM);
	size += sphinxLoadState(&sphinx0, statePtr+size);
	size += V30LoadState(&V30OpTable, statePtr+size);
	memcpy(wsSRAM, statePtr+size, sizeof(wsSRAM));
	size += sizeof(wsSRAM);
	size += wsEepromLoadState(&extEeprom, statePtr+size);
}

int getStateSize() {
	int size = 0;
	size += sizeof(wsRAM);
	size += sphinxGetStateSize();
	size += V30GetStateSize();
	size += sizeof(wsSRAM);
	size += wsEepromGetStateSize();
	return size;
}

static void setupBorderPalette(const void *palette, int len) {
//	monoPalInit(gGammaValue, gContrastValue);
	if (gBorderEnable == 0) {
		memset(EMUPALBUFF, 0, len);
	}
	else {
		memcpy(EMUPALBUFF, palette, len);
	}
//	paletteTxAll();					// Make new palette visible
}

void setupWSBackground() {
	LZ77UnCompVram(WSBorderTiles, TILE_BASE_ADR(1));
	LZ77UnCompVram(WSBorderMap, MAP_BASE_ADR(15));
}

void setupWSBorderPalette() {
	setupBorderPalette(WSBorderPal, WSBorderPalLen);
}

void setupWSCBackground() {
	LZ77UnCompVram(WSCBorderTiles, TILE_BASE_ADR(1));
	LZ77UnCompVram(WSCBorderMap, MAP_BASE_ADR(15));
}

void setupWSCBorderPalette() {
	setupBorderPalette(WSCBorderPal, WSCBorderPalLen);
}

void setupPCV2Background() {
	LZ77UnCompVram(PCV2BorderTiles, TILE_BASE_ADR(1));
	LZ77UnCompVram(PCV2BorderMap, MAP_BASE_ADR(15));
}

void setupPCV2BorderPalette() {
	setupBorderPalette(PCV2BorderPal, PCV2BorderPalLen);
}

void setupEmuBackground() {
	if (gMachine == HW_WONDERSWANCOLOR || gMachine == HW_SWANCRYSTAL) {
		setupWSCBackground();
		setupWSCBorderPalette();
	}
	else if (gMachine == HW_WONDERSWAN) {
		setupWSBackground();
		setupWSBorderPalette();
	}
	else {
		setupPCV2Background();
		setupPCV2BorderPalette();
	}
}

void setupEmuBorderPalette() {
	if (gMachine == HW_WONDERSWANCOLOR || gMachine == HW_SWANCRYSTAL) {
		setupWSCBorderPalette();
	}
	else if (gMachine == HW_WONDERSWAN) {
		setupWSBorderPalette();
	}
	else {
		setupPCV2BorderPalette();
	}
}
