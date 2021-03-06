/******************************************************************************
 * $Id: 
 *
 * Project:  OpenCPN
 * Purpose:  
 * Author:   dsr
 *
 ***************************************************************************
 *   Copyright (C) 2016 by David S. Register                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 ***************************************************************************
 */

#ifndef _TENDERPI_H_
#define _TENDERPI_H_

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#define     PLUGIN_VERSION_MAJOR    0
#define     PLUGIN_VERSION_MINOR    2

#define     MY_API_VERSION_MAJOR    1
#define     MY_API_VERSION_MINOR    12

#include "graphics.h"

#include <wx/notebook.h>
#include <wx/fileconf.h>
#include <wx/listctrl.h>
#include <wx/imaglist.h>
#include <wx/spinctrl.h>
#include <wx/aui/aui.h>
#include <wx/fontpicker.h>
//#include "/home/dsr/Projects/opencpn_sf/opencpn/include/ocpn_plugin.h"
#include "ocpn_plugin.h"

#include "nmea0183/nmea0183.h"
#include "PI_RolloverWin.h"
#include "TexFont.h"
#include "vector2d.h"
#include "OCPN_DataStreamEvent.h"

#define EPL_TOOL_POSITION -1          // Request default positioning of toolbar tool

#define gps_watchdog_timeout_ticks  10

//    Constants
#ifndef PI
#define PI        3.1415926535897931160E0      /* pi */
#endif

#define SEL_POINT_A     0
#define SEL_POINT_B     1
#define SEL_SEG         2

//      Menu items
#define ID_EPL_DELETE           8867
#define ID_EPL_XMIT             8868

//----------------------------------------------------------------------------------------------------------
//    Forward declarations
//----------------------------------------------------------------------------------------------------------
class brg_line;
class Select;
class SelectItem;
class PI_EventHandler;
class PI_OCP_DataStreamInput_Thread;

WX_DECLARE_OBJARRAY(brg_line *, ArrayOfBrgLines);
WX_DECLARE_OBJARRAY(vector2D *, ArrayOf2DPoints);

//void AlphaBlending( wxDC *pdc, int x, int y, int size_x, int size_y, float radius, wxColour color,
//                    unsigned char transparency );
//void RenderLine(int x1, int y1, int x2, int y2, wxColour color, int width);
//void GLDrawLine( wxCoord x1, wxCoord y1, wxCoord x2, wxCoord y2 );
//void RenderGLText( wxString &msg, wxFont *font, int xp, int yp, double angle);

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------


class tender_pi : public wxTimer, opencpn_plugin_112
{
public:
      tender_pi(void *ppimgr);
      ~tender_pi(void);

//    The required PlugIn Methods
      int Init(void);
      bool DeInit(void);


      int GetAPIVersionMajor();
      int GetAPIVersionMinor();
      int GetPlugInVersionMajor();
      int GetPlugInVersionMinor();
      wxBitmap *GetPlugInBitmap();
      wxString GetCommonName();
      wxString GetShortDescription();
      wxString GetLongDescription();

//    The optional method overrides
      void SetNMEASentence(wxString &sentence);
      void SetPositionFix(PlugIn_Position_Fix &pfix);
      void SetCursorLatLon(double lat, double lon);
      int GetToolbarToolCount(void);
      void OnToolbarToolCallback(int id);
//      void ShowPreferencesDialog( wxWindow* parent );
      void SetColorScheme(PI_ColorScheme cs);

      bool RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp);
      bool RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp);
      bool MouseEventHook( wxMouseEvent &event );   
      
      void OnRolloverPopupTimerEvent( wxTimerEvent& event );
      void PopupMenuHandler( wxCommandEvent& event );
      
      bool SaveConfig(void);
      void PopulateContextMenu( wxMenu* menu );
      int GetToolbarItemId(){ return m_toolbar_item_id; }
      void SetPluginMessage(wxString &message_id, wxString &message_body);

      void ProcessTimerEvent( wxTimerEvent& event );
      void RenderFixHat( void );
      void ShowPreferencesDialog( wxWindow* parent );

      //    Secondary thread life toggle
      //    Used to inform launching object (this) to determine if the thread can
      //    be safely called or polled, e.g. wxThread->Destroy();
      void SetSecThreadActive(void){m_bsec_thread_active = true;}
      void SetSecThreadInActive(void){m_bsec_thread_active = false;}
      bool IsSecThreadActive(){ return m_bsec_thread_active; }
      bool                m_bsec_thread_active;
      int                 m_Thread_run_flag;
 
      void ProcessTenderFix( void );
      
private:
      bool LoadConfig(void);
      void ApplyConfig(void);
      
      void setIcon( char ** xpm_bits);
      void RenderIconDC( wxDC &dc );
      void RenderIconGL( );
      
      void ComputeShipScaleFactor(float icon_hdt, int ownShipWidth, int ownShipLength, 
                                             wxPoint &lShipMidPoint, wxPoint &GPSOffsetPixels,
                                             wxPoint lGPSPoint, float &scale_factor_x, float &scale_factor_y);
      
      
      
      void ProcessBrgCapture(double brg_rel, double brg_subtended, double brg_TM, int brg_TM_flag,
                                wxString Ident, wxString target);

      int CalculateFix( void );
      void setTrackedWPSelect(wxString GUID);
      
      void startSerial(const wxString &port);
      void stopSerial( void );
      
      wxBitmap         *m_pplugin_icon;
      wxFileConfig     *m_pconfig;
      int              m_toolbar_item_id;

      int               m_show_id;
      int               m_hide_id;

      NMEA0183             m_NMEA0183;                 // Used to parse NMEA Sentences
      // FFU
      int                  m_config_version;
      wxString             m_VDO_accumulator;

      Select               *m_select;
      
      ArrayOfBrgLines      m_brg_array;
      double               m_fix_lat;
      double               m_fix_lon;
      ArrayOf2DPoints      m_hat_array;
      int                  m_nfix;
      bool                 m_bshow_fix_hat;
      
      //        Selection variables
      brg_line             *m_sel_brg;
      int                  m_sel_part;
      SelectItem           *m_pFind;
      double               m_sel_pt_lat;
      double               m_sel_pt_lon;
      double               m_segdrag_ref_x;
      double               m_segdrag_ref_y;
      double               m_cursor_lat;
      double               m_cursor_lon;
      int                  m_mouse_x;
      int                  m_mouse_y;
      
      //        State variables captured from NMEA stream
      int                  mHDx_Watchdog;
      int                  mHDT_Watchdog;
      int                  mGPS_Watchdog;
      int                  mVar_Watchdog;
      double               mVar;
//      double               mHdm;
      double               m_ownship_cog;
      bool                 m_head_active;
      wxTimer              m_head_dog_timer;
      
      
      int                  mPriPosition;
      int                  mPriDateTime;
      int                  mPriVar;
      int                  mPriHeadingM;
      int                  mPriHeadingT;
      
      double               m_ownship_lat;
      double               m_ownship_lon;
      double               m_hdt;
      wxDateTime           mUTCDateTime;

     
      //        Rollover Window support
      brg_line             *m_pRolloverBrg;
      RolloverWin          *m_pBrgRolloverWin;
      wxTimer               m_RolloverPopupTimer;
      int                   m_rollover_popup_timer_msec;
      
      wxColour              m_FixHatColor;

      PI_EventHandler       *m_event_handler;
      PI_OCP_DataStreamInput_Thread *m_serialThread;
      wxString              m_serialPort;
      
     wxBitmap               m_tender_bmp;
     unsigned int           m_iconTexture;
     int                    m_texwidth, m_texheight;
     
     SelectItem             *m_tenderSelect;
     wxString               m_trackedWP;
     wxString               m_trackedWPGUID;
     
     int                    m_tenderGPS_x;
     int                    m_tenderGPS_y;
     int                    m_tenderLength;
     int                    m_tenderWidth;
     
     wxString               m_tenderIconType;
     PlugIn_Waypoint        m_TrackedWP;
     
     RolloverWin            *m_pTrackRolloverWin;

     DECLARE_EVENT_TABLE();
     
};



//      An event handler to manage timer ticks, and the like
class PI_EventHandler : public wxEvtHandler
{
public:
    PI_EventHandler( tender_pi *parent);
    ~PI_EventHandler();
    
    void OnTimerEvent( wxTimerEvent& event );
    void PopupMenuHandler(wxCommandEvent& event );
    void OnEvtOCPN_NMEA(PI_OCPN_DataStreamEvent & event);
    
private:
    tender_pi              *m_parent;
    
    DECLARE_EVENT_TABLE();
    
};


typedef enum BearingTypeEnum
{
    MAG_BRG = 0,
    TRUE_BRG
}_BearingTypeEnum;


//    Generic Bearing line class definition
class brg_line
{
public:
    brg_line(double bearing, BearingTypeEnum type);
    brg_line(double bearing, BearingTypeEnum type, double lat_point, double lon_point, double length);
    ~brg_line();
 
    // Accessors
    void SetColor(wxColour &color);
    void SetWidth(int width);
    void SetStyle(int style);
    double GetLatA(){ return m_latA; }
    double GetLonA(){ return m_lonA; }
    double GetLatB(){ return m_latB; }
    double GetLonB(){ return m_lonB; }
    double GetBearingTrue(){ return m_bearing_true; }
    
    void SetIdent(wxString Ident){ m_Ident = Ident; }
    void SetTargetName( wxString target){ m_TargetName = target; };
    wxString GetIdent(){ return m_Ident; }
    wxString GetTargetName(){ return m_TargetName; }
    
    void CalcPointB( void );
    void CalcLength( void );
    
    //  Public methods
    void Draw( void );
    void DrawInfoBox( void );
    void DrawInfoAligned( void );

    bool getIntersect(brg_line *b, double *lat, double *lon);
        
    
    double      m_latA;
    double      m_lonA;
    double      m_latB;
    double      m_lonB;
    
    
private:
    //  Methods
    void        Init(void);
    
    
    wxString    m_TargetName;
    wxString    m_Ident;
    
    BearingTypeEnum m_type;
    double      m_bearing;
    double      m_bearing_true;
    
    
    double      m_length;   // Nautical Miles
 
    wxColour    m_color;
    int         m_width;
    wxFont      *m_Font;
    wxColour    m_color_text;
    
    wxDateTime   m_create_time;
    wxColour    m_InfoBoxColor;
    
};



class TenderPrefsDialog : public wxDialog 
{
private:
    
protected:
    wxStdDialogButtonSizer* m_sdbSizer1;
    wxButton* m_sdbSizer1OK;
    wxButton* m_sdbSizer1Cancel;
    
public:
//     wxRadioBox* m_rbViewType;
//     wxCheckBox* m_cbShowPlotOptions;
//     wxCheckBox* m_cbShowAtCursor;
//     wxCheckBox* m_cbLiveIcon;
//     wxCheckBox* m_cbShowIcon;
//     wxSlider* m_sOpacity;
    
    wxComboBox *m_comboPort;
    wxArrayString *m_pSerialArray;

   
    wxComboBox  *m_wpComboPort;
    
    wxString  m_trackedPointName;
    wxString  m_trackedPointGUID;
    
    wxComboBox  *m_comboIcon;
    wxTextCtrl *m_pTenderGPSOffsetX;
    wxTextCtrl *m_pTenderGPSOffsetY;
    wxTextCtrl *m_pTenderLength;
    wxTextCtrl *m_pTenderWidth;
    
    
    TenderPrefsDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("WMM Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE ); 
    ~TenderPrefsDialog();
    void OnTenderPrefsOkClick(wxCommandEvent& event);
    
    DECLARE_EVENT_TABLE()
    
    
    
};

#endif

