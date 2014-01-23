tagMenu: loadTagRecord
If [ $$stopLoadTagRecord ≠ 1 ]
#
Allow User Abort [ Off ]
Set Error Capture [ On ]
#Capture recordID to conditionally format current record.
Set Variable [ $$tagRecordID; Value:Get (RecordID) ]
#
// #If in add mode, capture the recordID to loop
// #back to it if user navigates away from original
// #add window.
// If [ $$add = 1 and $$citationMatch = $$addCitationMatch ]
// Set Variable [ $$addRecord; Value:tagMenus::_Ltag ]
// Else If [ $$add = "" ]
// Set Variable [ $$addRecord ]
// End If
Refresh Window
Perform Script [ “checkIfLockedOnLearnTagMenus” ]
Go to Field [ ]
End If
#
#NOTE: this script is used on the Tag Menus window
#for Learn records to exit ﬁeld when a record is
#is ﬁrst entered, which is a real problem on the
#iPhone as the text edit box opens when the user
#may have clicked only to select the record rather
#than edit it.
# This ﬁeld exit command is in the citation load
#script along with a lot of other commands which
#are not needed in this case. Thus I choose the
#smaller script, which also has conditional formatting
#step which is not used here, but is needed on
#on other layouts.
# SO...light script with unused command instead
#of heavy script orginally written for loading these
#records when they are main records (here they
#are just tag records).
January 7, 平成26 16:23:15 Imagination Quality Management.fp7 - loadTagRecord -1-
