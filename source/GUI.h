#ifndef GUI_HEADER
#define GUI_HEADER

#ifdef __cplusplus
extern "C" {
#endif

extern u8 gGammaValue;

void setupGUI(void);
void enterGUI(void);
void exitGUI(void);
void quickSelectGame(void);
void nullUINormal(int key);
void nullUIDebug(int key);
void resetGame(void);

void uiNullNormal(void);
void uiMainMenu(void);
void uiFile(void);
void uiSettings(void);
void uiController(void);
void uiDisplay(void);
void uiAbout(void);
void uiLoadGame(void);

void debugIOUnmappedR(u8 port);
void debugIOUnmappedW(u8 port, u8 val);
void debugIOUnimplR(u8 port);
void debugIOUnimplW(u8 port, u8 val);

void controllerSet(void);
void swapABSet(void);

void scalingSet(void);
void gammaSet(void);
void fgrLayerSet(void);
void bgrLayerSet(void);
void sprLayerSet(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // GUI_HEADER
