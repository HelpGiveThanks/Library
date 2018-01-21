January 18, 2018 15:34:57 Library.fmp12 - finishReferenceEdit -1-
reference: finishReferenceEdit
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#If in an unlocked reference edit window...
If [ refCreatorNode::orderOrLock = "" ]
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Field [ ]
Select Window [ Name: "References"; Current file ]
Go to Field [ ]
#
#If media and media type have not been
#selected then tell user that these fields are
#required before exiting the reference record.
If [ reference::kisWhat = "" and TEMP::InventoryLibraryYN = "" or Right ( Filter (isON::isON_Pulldown ; "—" ) ; 1 ) = "—" ]
Show Custom Dialog [ Message: "REQUIRED: Click on " & Quote ( "What's it on/in?" ) & " pulldown menu and make a
selection."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
Else If [ reference::kisON = "" and TEMP::InventoryLibraryYN = "" or Right ( Filter (isWhat::isWhat_Pulldown ; "—" ) ; 1 ) = "—" ]
Show Custom Dialog [ Message: "REQUIRED: Click on " & Quote ( "What is it?" ) & " pulldown menu and make a
selection."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#If the user is leaving the edit layout with
#copyright check boxes checked for which there
#is no copyright holder, inform them of this and
#give them option to fix this.
If [ Filter ( reference::kcopyrightHolder ; "1" ) = 1 and reference::knodeOther = "" and reference::knodePrimary = "" and reference::
referenceNodes = "" ]
Set Variable [ $blankCopyrightHolders; Value:"Author" ]
End If
If [ Filter ( reference::kcopyrightHolder ; "2" ) = 2 and reference::governmentAuthor = "" ]
Set Variable [ $blankCopyrightHolderNew; Value:Case ( $blankCopyrightHolders = "" ; "" ; $blankCopyrightHolders & ", " ) &
"Government Author" ]
Set Variable [ $blankCopyrightHolders; Value:$blankCopyrightHolderNew ]
End If
If [ Filter ( reference::kcopyrightHolder ; "3" ) = 3 and reference::compilationEditors = "" ]
Set Variable [ $blankCopyrightHolderNew; Value:Case ( $blankCopyrightHolders = "" ; "" ; $blankCopyrightHolders & ", " ) &
"Editor" ]
Set Variable [ $blankCopyrightHolders; Value:$blankCopyrightHolderNew ]
End If
If [ Filter ( reference::kcopyrightHolder ; "4" ) = 4 and reference::kpublication = "" ]
Set Variable [ $blankCopyrightHolderNew; Value:Case ( $blankCopyrightHolders = "" ; "" ; $blankCopyrightHolders & ", " ) &
"Publication" ]
Set Variable [ $blankCopyrightHolders; Value:$blankCopyrightHolderNew ]
End If
If [ Filter ( reference::kcopyrightHolder ; "5" ) = 5 and reference::kpublisher = "" ]
Set Variable [ $blankCopyrightHolderNew; Value:Case ( $blankCopyrightHolders = "" ; "" ; $blankCopyrightHolders & ", " ) &
"Publisher" ]
Set Variable [ $blankCopyrightHolders; Value:$blankCopyrightHolderNew ]
End If
If [ Filter ( reference::kcopyrightHolder ; "6" ) = 6 and reference::copyrightOtherHolder = "" ]
Set Variable [ $blankCopyrightHolderNew; Value:Case ( $blankCopyrightHolders = "" ; "" ; $blankCopyrightHolders & ", " ) &
"Other copyright holder" ]
Set Variable [ $blankCopyrightHolders; Value:$blankCopyrightHolderNew ]
End If
If [ $blankCopyrightHolders ≠ "" ]
Show Custom Dialog [ Message: "The following copyright checkboxes where checked, but no copyright holder was
specified for them: "
&
$blankCopyrightHolders
& ". Fix this later or now?"; Default Button: “now”, Commit: “Yes”; Button 2: “later”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 1 ]
Exit Script [ ]
End If
End If
#
#
If [ reference::showMedia[1] and reference::URL = "" ]
Show Custom Dialog [ Message: "You have checked the Picture's display web media box, BUT, you deleted the url (web
address) for this media (located in the Public copy location area below). Fix this later or now?"; Default Button: “now”,
Commit: “Yes”; Button 2: “later”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 1 ]
Exit Script [ ]
End If
End If
#
#
End If
#
#
#Clear file name variable used to determine
#valid file types.
Set Variable [ $$fileNameFieldHasMedia ]
#
#See if the edited record changed position in
#the main reference window as a result of
#alphabetical or order number changing edits.
Set Variable [ $$stoploadCitation ]
Select Window [ Name: "Hidden"; Current file ]
#
#If the edited record moved then note this.
#Later in this script, if the record did move,
#then the main reference window will have to
#be re-sorted to scroll to it in the reference window
#on the moved, edited record.
If [ $$editRecord ≠ Get (RecordNumber) ]
Set Variable [ $recordMoved; Value:Get (RecordNumber) ]
End If
#
#Close editing window
Close Window [ Name: "References"; Current file ]
Select Window [ Name: "Hidden"; Current file ]
Set Window Title [ Current Window; New Title: "References" ]
#
#Resort by subject and scroll to edited record.
If [ $recordMoved ≠ "" ]
Scroll Window
[ End ]
Sort Records [ ]
[ No dialog ]
End If
#
#Allow add mode.
Set Variable [ $$stopAdd ]
#
#Close reference help window if open.
Close Window [ Name: "Reference Field Help"; Current file ]
Close Window [ Name: "View Reference"; Current file ]
#
#Turn off editing variables.
Set Variable [ $$editRecord ]
Set Variable [ $$stoploadCitation ]
Set Variable [ $$turnOffThisScript ]
#
