#pragma once

#include "../defines.hpp"
#include <vector>
#include "WLSurface.hpp"

class CPopup;

class CSubsurface {
  public:
    // root dummy nodes
    CSubsurface(PHLWINDOW pOwner);
    CSubsurface(CPopup* pOwner);

    // real nodes
    CSubsurface(wlr_subsurface* pSubsurface, PHLWINDOW pOwner);
    CSubsurface(wlr_subsurface* pSubsurface, CPopup* pOwner);

    ~CSubsurface();

    Vector2D coordsRelativeToParent();
    Vector2D coordsGlobal();

    Vector2D size();

    void     onCommit();
    void     onDestroy();
    void     onNewSubsurface(wlr_subsurface* pSubsurface);
    void     onMap();
    void     onUnmap();

    void     recheckDamageForSubsurfaces();

  private:
    DYNLISTENER(destroySubsurface);
    DYNLISTENER(commitSubsurface);
    DYNLISTENER(newSubsurface);
    DYNLISTENER(mapSubsurface);
    DYNLISTENER(unmapSubsurface);

    wlr_subsurface* m_pSubsurface = nullptr;
    CWLSurface      m_sWLSurface;
    Vector2D        m_vLastSize = {};

    // if nullptr, means it's a dummy node
    CSubsurface*                              m_pParent = nullptr;

    PHLWINDOWREF                              m_pWindowParent;
    CPopup*                                   m_pPopupParent = nullptr;

    std::vector<std::unique_ptr<CSubsurface>> m_vChildren;

    bool                                      m_bInert = false;

    void                                      initSignals();
    void                                      initExistingSubsurfaces(wlr_surface* pSurface);
    void                                      checkSiblingDamage();
};