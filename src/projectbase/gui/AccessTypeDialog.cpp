#include "AccessTypeDialog.h"

// constructor and destructor ///////////////////////////////////////////////////////

udAccessTypeDialog::udAccessTypeDialog(wxWindow *parent) : udChoiceDialog( parent )
{
	wxString choices[] = {wxT("public"), wxT("protected"), wxT("private")};

	SetChoices( 3, choices );
	SetTitle( _("Access type") );
	SetComment( _("Select access type to this class member:") );
}

udAccessTypeDialog::~udAccessTypeDialog()
{
}
