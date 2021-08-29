/* https://gitlab.freedesktop.org/xorg/xserver/-/tree/9cd746bd0d5c23f0929342cb3cbe17f0c8407d37/mi */

/* List of built-in (statically linked) extensions */
static ExtensionModule staticExtensions[] = {
#ifdef BEZIER
    { BezierExtensionInit, "BEZIER", NULL, NULL, NULL },
#endif
#ifdef XTESTEXT1
    { XTestExtension1Init, "XTEST1", &noTestExtensions, NULL, NULL },
#endif
#ifdef MITSHM
    { ShmExtensionInit, SHMNAME, NULL, NULL, NULL },
#endif
#ifdef XINPUT
    { XInputExtensionInit, "XInputExtension", NULL, NULL, NULL },
#endif
#ifdef XTEST
    { XTestExtensionInit, XTestExtensionName, &noTestExtensions, NULL, NULL },
#endif
#ifdef XIDLE
    { XIdleExtensionInit, "XIDLE", NULL, NULL, NULL },
#endif
#ifdef XKB
    { XkbExtensionInit, XkbName, &noXkbExtension, NULL, NULL },
#endif
#ifdef LBX
    { LbxExtensionInit, LBXNAME, NULL, NULL, NULL },
#endif
#ifdef XAPPGROUP
    { XagExtensionInit, XAGNAME, NULL, NULL, NULL },
#endif
#ifdef XCSECURITY
    { SecurityExtensionInit, SECURITY_EXTENSION_NAME, NULL, NULL, NULL },
#endif
#ifdef XPRINT
    { XpExtensionInit, XP_PRINTNAME, NULL, NULL, NULL },
#endif
#ifdef PANORAMIX
    { PanoramiXExtensionInit, PANORAMIX_PROTOCOL_NAME, &noPanoramiXExtension, NULL, NULL },
#endif
#ifdef XF86BIGFONT
    { XFree86BigfontExtensionInit, XF86BIGFONTNAME, NULL, NULL, NULL },
#endif
#ifdef RENDER
    { RenderExtensionInit, "RENDER", NULL, NULL, NULL },
#endif
#ifdef RANDR
    { RRExtensionInit, "RANDR", NULL, NULL, NULL },
#endif
    { NULL, NULL, NULL, NULL, NULL }
};
    
/*ARGSUSED*/
void
InitExtensions(argc, argv)
    int		argc;
    char	*argv[];
{
    int i;
    ExtensionModule *ext;
    static Bool listInitialised = FALSE;

    if (!listInitialised) {
	/* Add built-in extensions to the list. */
	for (i = 0; staticExtensions[i].name; i++)
	    LoadExtension(&staticExtensions[i], TRUE);

	/* Sort the extensions according the init dependencies. */
	LoaderSortExtensions();
	listInitialised = TRUE;
    }

    for (i = 0; ExtensionModuleList[i].name != NULL; i++) {
	ext = &ExtensionModuleList[i];
	if (ext->initFunc != NULL && 
	    (ext->disablePtr == NULL || 
	     (ext->disablePtr != NULL && !*ext->disablePtr))) {
	    (ext->initFunc)();
	}
    }
}
