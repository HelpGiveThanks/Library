January 15, 2018 17:31:23 Library.fmp12 - showRefWebMedia -1-
pictures: showRefWebMedia
#
#
#Inform user if they have not entered a URL.
If [ reference::URL = "" and reference::picture = "" and reference::showMedia ≠ ""
or
reference::URL = "" and reference::picture = "Replace Me. Media Required" and reference::showMedia ≠ "" ]
Set Field [ reference::showMedia; "" ]
Go to Field [ ]
Show Custom Dialog [ Message: "Enter a valid URL below (web address) to see webmedia displayed here."; Default Button:
“OK”, Commit: “Yes” ]
Exit Script [ ]
#
#Inform user that the picture field is filled and must be
#cleared before they can display other media, unless
#the picture field is filled with a placeholder, in which
#case delete the place holder and show the
#other media.
Else If [ reference::picture ≠ "" ]
If [ reference::picture = "Replace Me. Media Required" ]
Set Field [ reference::picture; "" ]
Go to Field [ ]
Exit Script [ ]
End If
Set Field [ reference::showMedia; "" ]
Go to Field [ ]
Show Custom Dialog [ Message: "You can click to view webmedia only if you first delete the current picture. 1) Click on the
picture. 2) Click 'X' in the popup window that opens."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#
#Remove check from HDD media box if checked
#so web media will show up.
Set Field [ reference::showMedia[2]; "" ]
Go to Field [ ]
#
#
#If media is in use then inform user if they
#attempt to edit it.
If [ reference::showMedia = "" and reference::showMedia[2] = "" ]
Set Variable [ $$showRefURLmedia; Value:1 ]
Perform Script [ “CHUNK_checkIfReferencePicIsInUse (new)” ]
Go to Field [ ]
Set Variable [ $$showRefURLmedia ]
If [ reference::picture = "Replace Me. Media Required" ]
Perform Script [ “showCitationPicture1inNewWindow (update)” ]
End If
End If
#
