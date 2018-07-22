July 20, 2018 21:32:36 Library.fmp12 - selectLearnRecordsTaggedReferenceRecord… -1-
pictures: selectLearnRecordsTaggedReferenceRecord
#
#If node is currenlty locked then stop script, inform user.
If [ tagTLNodePrimary::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "The node — " & tagTLNodePrimary::tag & " — is locked. Go to the Default Node Tag Menu
and A) click 'lock' to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#This script is activited by the picture
#selection button on the QV layout. It allows
#the user to show a selected reference's
#media in the layout's picture window.
If [ testlearn::picture = "" ]
If [ testlearn::kshowReferencedMedia = refLearn::_Lreference ]
Set Field [ testlearn::kshowReferencedMedia; "" ]
Set Variable [ $$refMediaSelectedToShow; Value:Case ( testlearn::kshowReferencedMedia = "" ; "" ; testlearn::
kshowReferencedMedia ) ]
Else If [ //There is a picture to show if...
refLearn::picture ≠ "" or
refLearn::showMedia ≠ "" and refLearn::URL ≠ "" or
refLearn::showMedia[2] ≠ "" and refLearn::kfileLocation ≠ "" and refLearn::fileName ≠ "" ]
Set Field [ testlearn::kshowReferencedMedia; refLearn::_Lreference ]
Set Variable [ $$refMediaSelectedToShow; Value:Case ( testlearn::kshowReferencedMedia = "" ; "" ; testlearn::
kshowReferencedMedia ) ]
Else
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "This reference has no media to show. Picture button will be a darker grey if there is
media to show."; Default Button: “OK”, Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "This location has no media to show. Picture button will be a darker grey if there is
media to show."; Default Button: “OK”, Commit: “Yes” ]
End If
End If
#
Else
#If the learn record has a picture then stop
#this script and tell the user to remove it
#before adding a reference picture.
Set Field [ testlearn::kshowReferencedMedia; "" ]
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "To show a reference picture, first remove the picture that is currently showing. 1) Click on
the picture. 2) Click the 'x' button in the picture window."; Default Button: “OK”, Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "To show a location picture, first remove the picture that is currently showing. 1) Click on
the picture. 2) Click the 'x' button in the picture window."; Default Button: “OK”, Commit: “Yes” ]
End If
End If
#
#
#Insure that FileMaker knows about change, or
#else the file and web button scripts will fail to
#calculate the change.
Commit Records/Requests
#
#
