/*********************************************************************
 * Name:      	DiagTest.cpp
 * Purpose:   	Implements testing diagram plugin
 * Author:    	Michal Bližňák
 * Created:
 * Copyright:
 * License:   	wxWidgets license (www.wxwidgets.org)
 *********************************************************************/

#include "DiagUml.h"
#include "Ids.h"

// plugin //////////////////////////////////////////////////////////////////////

static udUmlDiagramPlugin *thePlugin = NULL;

long IDM_TRANS_CREATECONDITION = IPluginManager::Get()->GetNewMenuId();
long IDM_TRANS_CREATEEVENT = IPluginManager::Get()->GetNewMenuId();
long IDM_TRANS_CREATEACTION = IPluginManager::Get()->GetNewMenuId();
long IDM_TRANS_ASSIGNGUARD = IPluginManager::Get()->GetNewMenuId();
long IDM_TRANS_ASSIGNACTION = IPluginManager::Get()->GetNewMenuId(udvMAX_ITEMS);
long IDM_DIAG_ASSIGNVARIABLE = IPluginManager::Get()->GetNewMenuId(udvMAX_ITEMS);
long IDM_DIAG_ASSIGNFUNCTION = IPluginManager::Get()->GetNewMenuId(udvMAX_ITEMS);
long IDM_DIAG_CLEARCONDITIONS = IPluginManager::Get()->GetNewMenuId(udvMAX_ITEMS);
long IDM_DIAG_CLEARACTIONS = IPluginManager::Get()->GetNewMenuId();
long IDM_ENUM_CLEARELEMENTS = IPluginManager::Get()->GetNewMenuId();
long IDM_COMPSTATE_ACTION = IPluginManager::Get()->GetNewMenuId();

long IDM_CLASS_CREATECONSTRUCTOR = IPluginManager::Get()->GetNewMenuId();
long IDM_CLASS_CREATEDESTRUCTOR = IPluginManager::Get()->GetNewMenuId();
long IDM_CLASS_CREATEVARIABLE = IPluginManager::Get()->GetNewMenuId();
long IDM_CLASS_CREATEFUNCTION = IPluginManager::Get()->GetNewMenuId();
long IDM_CLASS_RENAMEVIRTUAL = IPluginManager::Get()->GetNewMenuId();
/*long IDM_CLASS_ACCESSTYPE = IPluginManager::Get()->GetNewMenuId();*/

long IDM_ENUM_ADDELEMENT = IPluginManager::Get()->GetNewMenuId(udvMAX_ITEMS);

//Define the plugin entry point
extern "C" WXDLLIMPEXP_CD IPlugin *CreatePlugin(IPluginManager *manager)
{
	if (thePlugin == NULL)
	{
		thePlugin = new udUmlDiagramPlugin(manager);
	}

	return thePlugin;
}

extern "C" WXDLLIMPEXP_CD udPluginInfo GetPluginInfo()
{
	// set plugin info
	udPluginInfo info;

	info.SetAuthor( wxT("Michal Bližňák") );
	info.SetName( _("UML diagrams") );
	info.SetDescription( _("Set of UML diagrams.") );
	info.SetType( udPluginInfo::ptDIAGRAM );
	info.SetVersion( wxT("1.0") );
	info.SetAPIVersionMin( 1 );
	info.SetAPIVersionMax( 1 );

	return info;
}

udUmlDiagramPlugin::udUmlDiagramPlugin(IPluginManager *manager) : IPlugin(manager)
{
}

bool udUmlDiagramPlugin::OnInit()
{
	// register bitmaps
	m_PluginManager->RegisterArtBitmap( wxT("plugins/project/Action.xpm"), wxT("udActionItem") );
	m_PluginManager->RegisterArtBitmap( wxT("plugins/project/Action_locked.xpm"), wxT("udImpActionItem") );
	m_PluginManager->RegisterArtBitmap( wxT("plugins/project/Action_link.xpm"), wxT("udActionLinkItem") );
	m_PluginManager->RegisterArtBitmap( wxT("plugins/project/Action_link.xpm"), wxT("udStateActionLinkItem") );
	m_PluginManager->RegisterArtBitmap( wxT("plugins/project/Condition.xpm"), wxT("udConditionItem") );
	m_PluginManager->RegisterArtBitmap( wxT("plugins/project/Condition_locked.xpm"), wxT("udImpConditionItem") );
	m_PluginManager->RegisterArtBitmap( wxT("plugins/project/Condition_link.xpm"), wxT("udConditionLinkItem") );
	m_PluginManager->RegisterArtBitmap( wxT("plugins/project/Event.xpm"), wxT("udEventItem") );
	m_PluginManager->RegisterArtBitmap( wxT("plugins/project/Event_locked.xpm"), wxT("udImpEventItem") );
	m_PluginManager->RegisterArtBitmap( wxT("plugins/project/Event_link.xpm"), wxT("udEventLinkItem") );
	m_PluginManager->RegisterArtBitmap( wxT("plugins/project/MemberData.xpm"), wxT("udMemberDataItem") );
	m_PluginManager->RegisterArtBitmap( wxT("plugins/project/MemberData_link.xpm"), wxT("udMemberDataLinkItem") );
	m_PluginManager->RegisterArtBitmap( wxT("plugins/project/MemberFunction.xpm"), wxT("udMemberFunctionItem") );
	m_PluginManager->RegisterArtBitmap( wxT("plugins/project/MemberFunction.xpm"), wxT("udConstructorFunctionItem") );
	m_PluginManager->RegisterArtBitmap( wxT("plugins/project/MemberFunction.xpm"), wxT("udDestructorFunctionItem") );
	m_PluginManager->RegisterArtBitmap( wxT("plugins/project/MemberFunction_link.xpm"), wxT("udMemberFunctionLinkItem") );
	m_PluginManager->RegisterArtBitmap( wxT("plugins/project/EnumVal.xpm"), wxT("udEnumValueItem") );

	// register diagrams
	udDiagramInfo infoSSCH;
	// set general info
/// NO TRANSLATE ?
	infoSSCH.SetName( udnSIMPLE_STATE_CHART );
	//infoSSCH.SetName( _("Simple State Chart") );
	infoSSCH.SetDataClassName( wxT("udSStateChartDiagramItem") );
	infoSSCH.SetIcon( wxT("plugins/project/SimpleStateChartDiag.xpm") );

	infoSSCH.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/State.xpm"), _("Simple state"), wxT("umlSimpleStateItem"), wxT("udSimpleStateElementItem"), udDiagramComponentInfo::pitELEMENT ) );
	infoSSCH.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/SubState.xpm"), _("Sub machine"), wxT("umlSubStateItem"), wxT("udSCHSubDiagramElementItem"), udDiagramComponentInfo::pitELEMENT ) );
	infoSSCH.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/Initial.xpm"), _("Initial"), wxT("umlInitialItem"), wxT("udInitialElementItem"), udDiagramComponentInfo::pitELEMENT ) );
	infoSSCH.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/Final.xpm"), _("Final"), wxT("umlFinalItem"), wxT("udFinalElementItem"), udDiagramComponentInfo::pitELEMENT ) );
	infoSSCH.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/Line1.xpm"), _("Transition connection"), wxT("umlTransitionItem"), wxT("udTransElementItem"), udDiagramComponentInfo::pitCONNECTION ) );

	m_PluginManager->RegisterDiagram( infoSSCH );

	udDiagramInfo infoHSCH;
/// NO TRANSLATE ?
	infoHSCH.SetName(udnSTATE_CHART );
//	infoHSCH.SetName(_("State Chart"));
	infoHSCH.SetDataClassName( wxT("udHStateChartDiagramItem") );
	infoHSCH.SetIcon( wxT("plugins/project/StateChartDiag.xpm") );

	infoHSCH.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/State.xpm"), _("Simple state"), wxT("umlSimpleStateItem"), wxT("udSimpleStateElementItem"), udDiagramComponentInfo::pitELEMENT ) );
	infoHSCH.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/CompState.xpm"), _("Composite machine"), wxT("umlCompStateItem"), wxT("udCompStateElementItem"), udDiagramComponentInfo::pitELEMENT ) );
	infoHSCH.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/SubState.xpm"), _("Sub machine"), wxT("umlSubStateItem"), wxT("udSCHSubDiagramElementItem"), udDiagramComponentInfo::pitELEMENT ) );
	infoHSCH.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/Initial.xpm"), _("Initial"), wxT("umlInitialItem"), wxT("udInitialElementItem"), udDiagramComponentInfo::pitELEMENT ) );
	infoHSCH.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/Final.xpm"), _("Final"), wxT("umlFinalItem"), wxT("udFinalElementItem"), udDiagramComponentInfo::pitELEMENT ) );
	infoHSCH.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/History.xpm"), _("History"), wxT("umlHistoryItem"), wxT("udHistoryElementItem"), udDiagramComponentInfo::pitELEMENT ) );
	infoHSCH.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/Decision.xpm"), _("Decision"), wxT("umlDecisionItem"), wxT("udDecisionElementItem"), udDiagramComponentInfo::pitELEMENT ) );
	infoHSCH.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/Line1.xpm"), _("Transition connection"), wxT("umlTransitionItem"), wxT("udTransElementItem"), udDiagramComponentInfo::pitCONNECTION ) );

	m_PluginManager->RegisterDiagram( infoHSCH );

	udDiagramInfo infoCD;
/// NO TRANSLATE ?
	infoCD.SetName(udnCLASS_DIAGRAM);
	//infoCD.SetName( _("Class Diagram"));
	infoCD.SetDataClassName( wxT("udClassDiagramItem") );
	infoCD.SetIcon( wxT("plugins/project/ClassDiag.xpm") );

	infoCD.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/Class.xpm"), _("Class"), wxT("umlClassItem"), wxT("udClassElementItem"), udDiagramComponentInfo::pitELEMENT ) );
	infoCD.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/ClassTempl.xpm"), _("Class template"), wxT("umlClassTemplateItem"), wxT("udClassTemplateElementItem"), udDiagramComponentInfo::pitELEMENT ) );
	infoCD.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/Enum.xpm"), _("Enumeration"), wxT("umlEnumItem"), wxT("udEnumElementItem"), udDiagramComponentInfo::pitELEMENT ) );
	infoCD.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/Line1.xpm"), _("Inheritance connection"), wxT("umlInheritanceItem"), wxT("udInherElementItem"), udDiagramComponentInfo::pitCONNECTION ) );
	infoCD.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/Line3.xpm"), _("Interface connection"), wxT("umlInterfaceItem"), wxT("udInterElementItem"), udDiagramComponentInfo::pitCONNECTION ) );
	infoCD.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/Line2.xpm"), _("Bi-directional association"), wxT("umlBiDirectAssocItem"), wxT("udBiAssocElementItem"), udDiagramComponentInfo::pitCONNECTION ) );
	infoCD.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/Line5.xpm"), _("Uni-directional association"), wxT("umlUniDirectAssocItem"), wxT("udUniAssocElementItem"), udDiagramComponentInfo::pitCONNECTION ) );
	infoCD.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/Line7.xpm"), _("Basic aggregation"), wxT("umlBasicAggregItem"), wxT("udBaseAggregElementItem"), udDiagramComponentInfo::pitCONNECTION ) );
	infoCD.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/Line6.xpm"), _("Composition aggregation"), wxT("umlCompAggregItem"), wxT("udCompAggregElementItem"), udDiagramComponentInfo::pitCONNECTION ) );
	infoCD.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/Line8.xpm"), _("Template binding"), wxT("umlTemplateBindItem"), wxT("udTemplateBindElementItem"), udDiagramComponentInfo::pitCONNECTION ) );
	infoCD.AddComponentInfo( udDiagramComponentInfo( wxT("plugins/elements/Line9.xpm"), _("Include association"), wxT("umlIncludeAssocItem"), wxT("udIncludeAssocElementItem"), udDiagramComponentInfo::pitCONNECTION ) );

	m_PluginManager->RegisterDiagram( infoCD );

	// register friendly names
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udTransElementItem"), _("Transition element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udCompStateElementItem"), _("Composite state element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udSubDiagramElementItem"), _("Sub diagram element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udSCHSubDiagramElementItem"), _("State chart sub diagram element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udHCHSubDiagramElementItem"), _("Hierarchical state chart sub diagram element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udSimpleStateElementItem"), _("Simple state element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udInitialElementItem"), _("Initial state element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udFinalElementItem"), _("Final state element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udDecisionElementItem"), _("Decision state element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udHistoryElementItem"), _("History state element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udClassElementItem"), _("Class element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udEnumElementItem"), _("Enumeration element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udEnumValueItem"), _("Enumeration value") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udIncludeAssocElementItem"), _("Include association element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udClassTemplateElementItem"), _("Class template element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udInherElementItem"), _("Inheritance element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udInterElementItem"), _("Interface element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udBiAssocElementItem"), _("Bi-directional association element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udUniAssocElementItem"), _("Uni-directional association element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udBaseAggregElementItem"), _("Basic aggregation element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udCompAggregElementItem"), _("Composition aggregation element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udConditionItem"), _("Condition function") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udEventItem"), _("Event flag") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udActionItem"), _("Action function") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udMemberDataItem"), _("Class member data") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udMemberFunctionItem"), _("Class member function") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udConstructorFunctionItem"), _("Class constructor") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udDestructorFunctionItem"), _("Class destructor") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udConditionLinkItem"), _("Condition function link") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udEventLinkItem"), _("Event flag link") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udActionLinkItem"), _("Action function link") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udStateActionLinkItem"), _("State action function link") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udElementLinkItem"), _("Element link") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udMemberDataLinkItem"), _("Class member data link") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udMemberFunctionLinkItem"), _("Class member function link") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udSCHSubDiagramItem"), _("State chart sub diagram") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udSStateChartDiagramItem"), _("Simple State Chart diagram") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udHStateChartDiagramItem"), _("Hierarchical State Chart diagram") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udClassDiagramItem"), _("Class diagram") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udTransElementItem"), _("Inheritance element") );

	m_PluginManager->RegisterFriendlyName( wxT("non_blocking"), wxT("0"), _("False") );
	m_PluginManager->RegisterFriendlyName( wxT("non_blocking"), wxT("1"), _("True") );

	m_PluginManager->RegisterFriendlyName( wxT("action_type"), wxT("0"), _("Entry action") );
	m_PluginManager->RegisterFriendlyName( wxT("action_type"), wxT("1"), _("Exit action") );

	m_PluginManager->RegisterFriendlyName( wxT("include_target_class"), wxT("0"), _("False") );
	m_PluginManager->RegisterFriendlyName( wxT("include_target_class"), wxT("1"), _("True") );

	m_PluginManager->RegisterFriendlyName( wxT("evt_type"), wxT("0"), _("Normal event") );
	m_PluginManager->RegisterFriendlyName( wxT("evt_type"), wxT("1"), _("Critical event") );

	m_PluginManager->RegisterFriendlyName( wxT("store_ret_val"), wxT("0"), _("False") );
	m_PluginManager->RegisterFriendlyName( wxT("store_ret_val"), wxT("1"), _("True") );

	// register event handlers
	wxWindow *pFrame = m_PluginManager->GetMainFrame();
	pFrame->Connect( IDM_TRANS_ASSIGNACTION, IDM_TRANS_ASSIGNACTION + udvMAX_ITEMS - 1, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignAction ), NULL, this );
	pFrame->Connect( IDM_TRANS_ASSIGNGUARD, IDM_TRANS_ASSIGNGUARD + udvMAX_ITEMS - 1, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignGuard ), NULL, this  );
	pFrame->Connect( IDM_DIAG_ASSIGNVARIABLE, IDM_DIAG_ASSIGNVARIABLE + udvMAX_ITEMS - 1, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignVariable ), NULL, this  );
	pFrame->Connect( IDM_DIAG_ASSIGNFUNCTION, IDM_DIAG_ASSIGNFUNCTION + udvMAX_ITEMS - 1, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignFunction ), NULL, this  );
	pFrame->Connect( IDM_DIAG_CLEARCONDITIONS, IDM_ENUM_CLEARELEMENTS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnClearCodeItems), NULL, this  );
	pFrame->Connect( IDM_TRANS_CREATECONDITION, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignNewCondition ), NULL, this  );
	pFrame->Connect( IDM_TRANS_CREATEEVENT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignNewEvent ), NULL, this  );
	pFrame->Connect( IDM_TRANS_CREATEACTION, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignNewAction ), NULL, this  );
	pFrame->Connect( IDM_CLASS_CREATEVARIABLE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignNewVariable ), NULL, this  );
	pFrame->Connect( IDM_CLASS_CREATEFUNCTION, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignNewFunction ), NULL, this  );
	pFrame->Connect( IDM_CLASS_CREATECONSTRUCTOR, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnCreateConstructor ), NULL, this  );
	pFrame->Connect( IDM_CLASS_CREATEDESTRUCTOR, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnCreateDestructor ), NULL, this  );
	pFrame->Connect( IDM_COMPSTATE_ACTION, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignNewStateAction ), NULL, this  );
	pFrame->Connect( IDM_CLASS_RENAMEVIRTUAL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnRefactorVirtualFcn ), NULL, this  );
	pFrame->Connect( IDM_CODE_ACCESSTYPE, IDM_CODE_ACCESSTYPE + udvMAX_ITEMS - 1, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnChangeAccessType ), NULL, this  );
	pFrame->Connect( IDM_ENUM_ADDELEMENT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAddEnumElement ), NULL, this );

	m_PluginManager->RegisterEventListener( this );

	// register code packages
	m_PluginManager->RegisterCodePackage( wxT("udActionItem"), _("Action functions") );
	m_PluginManager->RegisterCodePackage( wxT("udConditionItem"), _("Condition functions") );
	m_PluginManager->RegisterCodePackage( wxT("udEventItem"), _("Event flags") );
	m_PluginManager->RegisterCodePackage( wxT("udMemberDataItem"), _("Class data members") );
	m_PluginManager->RegisterCodePackage( wxT("udMemberFunctionItem"), _("Class member functions") );
	m_PluginManager->RegisterCodePackage( wxT("udConstructorFunctionItem"), _("Constructors/destructors") );
	m_PluginManager->RegisterCodePackage( wxT("udDestructorFunctionItem"), _("Constructors/destructors") );

	return true;
}

int udUmlDiagramPlugin::OnExit()
{
	// unregister event handlers
	wxWindow *pFrame = m_PluginManager->GetMainFrame();
	pFrame->Disconnect( IDM_TRANS_ASSIGNACTION, IDM_TRANS_ASSIGNACTION + udvMAX_ITEMS - 1, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignAction ), NULL, this );
	pFrame->Disconnect( IDM_TRANS_ASSIGNGUARD, IDM_TRANS_ASSIGNGUARD + udvMAX_ITEMS - 1, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignGuard ), NULL, this  );
	pFrame->Disconnect( IDM_DIAG_ASSIGNVARIABLE, IDM_DIAG_ASSIGNVARIABLE + udvMAX_ITEMS - 1, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignVariable ), NULL, this  );
	pFrame->Disconnect( IDM_DIAG_ASSIGNFUNCTION, IDM_DIAG_ASSIGNFUNCTION + udvMAX_ITEMS - 1, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignFunction ), NULL, this  );
	pFrame->Disconnect( IDM_DIAG_CLEARCONDITIONS, IDM_ENUM_CLEARELEMENTS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnClearCodeItems), NULL, this  );
	pFrame->Disconnect( IDM_TRANS_CREATECONDITION, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignNewCondition ), NULL, this  );
	pFrame->Disconnect( IDM_TRANS_CREATEEVENT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignNewEvent ), NULL, this  );
	pFrame->Disconnect( IDM_TRANS_CREATEACTION, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignNewAction ), NULL, this  );
	pFrame->Disconnect( IDM_CLASS_CREATEVARIABLE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignNewVariable ), NULL, this  );
	pFrame->Disconnect( IDM_CLASS_CREATEFUNCTION, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignNewFunction ), NULL, this  );
	pFrame->Disconnect( IDM_CLASS_CREATECONSTRUCTOR, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnCreateConstructor ), NULL, this  );
	pFrame->Disconnect( IDM_CLASS_CREATEDESTRUCTOR, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnCreateDestructor ), NULL, this  );
	pFrame->Disconnect( IDM_COMPSTATE_ACTION, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAssignNewStateAction ), NULL, this  );
	pFrame->Disconnect( IDM_CLASS_RENAMEVIRTUAL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnRefactorVirtualFcn ), NULL, this  );
	pFrame->Disconnect( IDM_CODE_ACCESSTYPE, IDM_CODE_ACCESSTYPE + udvMAX_ITEMS - 1, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnChangeAccessType ), NULL, this  );
	pFrame->Disconnect( IDM_ENUM_ADDELEMENT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( udUmlDiagramPlugin::OnAddEnumElement ), NULL, this );

	m_PluginManager->UnregisterEventListener( this );

	return 0;
}

udPluginInfo udUmlDiagramPlugin::GetInfo()
{
	return GetPluginInfo();
}
