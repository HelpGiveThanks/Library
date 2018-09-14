August 30, 2018 13:05:47 Library.fmp12 - showCitationPicture1inNewWindow -1-
pictures: showCitationPicture1inNewWindow
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#
#Stop script if user clicked in the media field to
#navigate to this record, and the media window
#is empty.
If [ $$stopOpenNewTextWindow = 1 ]
Set Variable [ $$stopOpenNewTextWindow ]
#Open picture window if there is a picture
#to show.
If [ testlearn::kshowReferencedMedia = "" and testlearn::picture = ""
and
testlearnReportTags::kshowReferencedMedia = "" and testlearnReportTags::picture = "" ]
Exit Script [ ]
End If
End If
#
#
#If on the Tag Menus learn layout and there
#is no media to show, exit this script.
If [ Get ( WindowName ) = "Tag Menus" and Get ( LayoutTableName ) = "testlearn" and testlearn::picture = "" and testlearn::
kshowReferencedMedia = "" ]
Exit Script [ ]
End If
#
#
#In inventory mode, if the user is not in any
#hidden fields, and there is no media for this
#record, and the user just activated this script
#by clicking on the empty media field, then
#show the hidden fields including the hidden
#media field so the user can click on it and add
#a media if they want to.
If [ Get ( WindowName ) = "Tag Menus" and reference::picture = "" and $$editLocation = reference::_Lreference and TEMP::
InventoryLibraryYN ≠ "" ]
If [ Get ( ActiveFieldName ) = "" ]
Go to Object [ Object Name: "tag 1" ]
Refresh Window
Halt Script
Else
Set Variable [ $$editLocation ]
Set Variable [ $openHIddenPicture; Value:1 ]
Refresh Window
End If
End If
Go to Field [ ]
#
#
#Make sure on layouts where long text field
#extends over the picture field AND when this
#field is has text because there is no picture to
#cover up, that this script is stopped, and the
#user is taken to this long text field instead of
#the picture window opening up.
If [ reference::referenceHidePicture ≠ "" and Get (LayoutTableName) = "reference" and Get (WindowName) = "Tag Menus" and
$openHIddenPicture = "" or
reference::referenceHidePicture ≠ "" and Get (LayoutName) = "TestInfoReference" ]
Set Variable [ $$stopGoToKeyTag; Value:1 ]
Perform Script [ “viewReference” ]
Exit Script [ ]
Else If [ Get (LayoutTableName) = "tagMenus" and tagMenus::tagTestTextItemOrLongTagField ≠ "" ]
Go to Object [ Object Name: "tag 1" ]
Exit Script [ ]
End If
#
#If in stuff/inventory mode and the user is in
#the reference section which does not have an
#edit screen, then tell user when they click on
#a picture that they cannot edit if its creator is
#locked. In reference mode, the user expects
#to see a view only picture window on the
#main reference list screen. The edit picture
#reference window only shows up in reference
#mode when the user is on the edit screen, but
#since in stuff mode the list view shows
#editable records, show this message so the
#user knows why they are not seeing an edit
#picture screen.
If [ TEMP::InventoryLibraryYN ≠ "" and Get(LayoutTableName) = "reference" and $$add = "" and Get (WindowName) ≠ "Tag Menus" ]
If [ refCreatorNode::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "The node that created this record — " & refCreatorNode::tag & " — is locked. Select this
node in the setup window and enter the password to unlock it, then you will able to edit records assigned to it."; Default
Button: “OK”, Commit: “Yes” ]
Else If [ TEMP::primaryNodeIsLocked ≠ "" ]
Show Custom Dialog [ Message: "The default primary node — " & TEMP::DEFAULTNodePrimaryName & " — is locked.
Go to the Default Node Tag Menu and A) click 'lock' to unlock it, B) select an unlocked node for the primary node, or C)
create a new primary node."; Default Button: “OK”, Commit: “No” ]
End If
End If
#
#If reference media is required and the user is on a
#reference edit layout, note this in case user decides
#to cancel the insert media section of this script.
If [ reference::picture = "Replace Me. Media Required" and Get (LayoutName) = "ReferenceEDIT"
 or
reference::picture = "Replace Me. Media Required" and Get (LayoutName) = "ReferenceStuff" ]
Set Field [ reference::picture; "" ]
Set Variable [ $$ReplaceMeMediaRequired; Value:1 ]
Go to Field [ ]
Else
Set Variable [ $$ReplaceMeMediaRequired ]
End If
#
#
#To prevent multiple copies of the media
#window being left open, always close it when
#starting this script.
Close Window [ Name: "Media"; Current file ]
#
#
#If the PRIMARY node is currenlty locked then
If [ $$add = "" ]
If [ TEMP::primaryNodeIsLocked ≠ "" ]
Set Variable [ $lock; Value:1 ]
// #If the primary node's CREATOR node is
// Else If [ TEMP::primaryNodesCreatorNodeIsLocked ≠ "" ]
// Set Variable [ $lock; Value:1 ]
#If the TEST SUBJECT node is locked then stop
Else If [ testSubsectionTestSubjectLock::orderOrLock = "0"
 or
ReportResultTestSubject::orderOrLock ≠ ""
 or
reportTestSubjectLock::orderOrLock = "0" ]
Set Variable [ $lock; Value:1 ]
#If the LEARN record's creator node is locked then stop
Else If [ tagTLNodePrimary::orderOrLock = "0"
 or
tagTLReportNodePrimary::orderOrLock = "0" ]
Set Variable [ $lock; Value:1 ]
#If the REFERENCE record's creator node is locked then stop
Else If [ refCreatorNode::orderOrLock = "0" or refLearnCreatorNodeLock::orderOrLock = "0" or refLearnTestCreatorNodeLock::
orderOrLock = "0" ]
Set Variable [ $lock; Value:1 ]
End If
End If
#
#
#
#Determine source of media and layout. This
#info/variables will determine whether to show
#user an edit or view-only window, and whether
#to show user a web, harddrive, or FileMaker
#media window.
#
#
#If user is on a reference layout...
If [ Get (LayoutTableName) = "tempSetup" or Get (LayoutTableName) = "reference" or Get (LayoutTableName) = "tagMenus" ]
Set Variable [ $referenceLayout; Value:1 ]
#
If [ Get (LayoutTableName) = "tempSetup" ]
#SETUP DEFAULTS WINDOW
If [ $$defaultTestSubjecPicture ≠ "" ]
Set Variable [ $picture; Value:$$defaultTestSubjecPicture ]
Set Variable [ $fileLocation; Value:$$fileLocation ]
Else If [ $$defaultPrimaryNodePicture ≠ "" ]
Set Variable [ $picture; Value:$$defaultPrimaryNodePicture ]
Set Variable [ $fileLocation; Value:$$fileLocation ]
Else
Set Variable [ $picture; Value:defaultNodesCopyright::Kpicture1 ]
Set Variable [ $fileLocation; Value:Case (
defaultNodeCopyrightsPicture::picture ≠ "" ; "database" ;
defaultNodeCopyrightsPicture::kfileLocation ≠ "" and defaultNodeCopyrightsPicture::fileName ≠ "" and
defaultNodeCopyrightsPicture::showMedia = "" ; "harddrive" ;
defaultNodeCopyrightsPicture::URL ≠ "" and defaultNodeCopyrightsPicture::showMedia ≠ "" ; "web" ;
"tag=none" ) ]
End If
#
Else If [ Get (LayoutTableName) = "reference" ]
#REFERENCE WINDOW
Set Variable [ $picture; Value:reference::_Lreference ]
Set Variable [ $fileLocation; Value:Case (
reference::picture ≠ "" ; "database" ;
reference::kfileLocation ≠ "" and reference::fileName ≠ "" and reference::showMedia[2] ≠ "" ; "harddrive" ;
reference::URL ≠ "" and reference::showMedia ≠ "" ; "web" ;
Case ( Get (LayoutName) = "ReferenceEDIT" or Get (LayoutName) = "ReferenceSTUFF" or Get (LayoutName) =
"learnMenuRefStuff" ; "none" ; "tag=none" )
) ]
If [ Get (LayoutName) = "ReferenceEDIT" and tagTLNodePrimary::orderOrLock = "" ]
Set Variable [ $referenceEDIT; Value:1 ]
End If
#
Else If [ Get (LayoutTableName) = "tagMenus" ]
#TAG MENUS WINDOW (Reference and Learn tags)
If [ $$picture = "" ]
Set Variable [ $picture; Value:tagMenus::Kpicture1 ]
Set Variable [ $fileLocation; Value:Case (
refPicture1::picture ≠ "" ; "database" ;
refPicture1::kfileLocation ≠ "" and refPicture1::fileName ≠ "" and refPicture1::showMedia = "" ; "harddrive" ;
refPicture1::URL ≠ "" and refPicture1::showMedia ≠ "" ; "web" ;
"tag=none" ) ]
Else If [ $$picture = "Kpicture2" ]
Set Variable [ $picture; Value:tagMenus::Kpicture2 ]
Set Variable [ $fileLocation; Value:Case (
refPicture2::picture ≠ "" ; "database" ;
refPicture2::kfileLocation ≠ "" and refPicture2::fileName ≠ "" and refPicture2::showMedia = "" ; "harddrive" ;
refPicture2::URL ≠ "" and refPicture2::showMedia ≠ "" ; "web" ;
"tag=none" ) ]
Else If [ $$picture = "Kpicture3" ]
Set Variable [ $picture; Value:tagMenus::Kpicture3 ]
Set Variable [ $fileLocation; Value:Case (
refPicture3::picture ≠ "" ; "database" ;
refPicture3::kfileLocation ≠ "" and refPicture3::fileName ≠ "" and refPicture3::showMedia = "" ; "harddrive" ;
refPicture3::URL ≠ "" and refPicture3::showMedia ≠ "" ; "web" ;
"tag=none" ) ]
End If
End If
#
#
#If user is on a learn layout...
Else If [ Get (LayoutTableName) = "testLearn" or Get (LayoutTableName) = "testlearnReportTags" or Get (LayoutTableName) =
"report" ]
Set Variable [ $learnLayout; Value:1 ]
#
If [ Get (LayoutTableName) = "testLearn" ]
#LEARN and TEST WINDOWS
Set Variable [ $picture; Value:testlearn::_Ltestlearn ]
Set Variable [ $fileLocation; Value:Case ( testlearn::picture ≠ "" ; "TLpicture" ;
Case (
refLearnShowMedia::picture ≠ "" ; "database" ;
refLearnShowMedia::kfileLocation ≠ "" and refLearnShowMedia::fileName ≠ "" and refLearnShowMedia::showMedia =
"" ; "harddrive" ;
refLearnShowMedia::URL ≠ "" and refLearnShowMedia::showMedia ≠ "" ; "web" ;
"none" )
) ]
#
Else If [ Get (LayoutTableName) = "testlearnReportTags" ]
#TEST INFO and REPORT INFO WINDOWS
Set Variable [ $picture; Value:testlearnReportTags::_Ltestlearn ]
Set Variable [ $fileLocation; Value:Case ( testlearnReportTags::picture ≠ "" ; "TLpicture" ;
Case (
refTestShowMedia::picture ≠ "" ; "database" ;
refTestShowMedia::kfileLocation ≠ "" and refTestShowMedia::fileName ≠ "" and refTestShowMedia::showMedia = "" ;
"harddrive" ;
refTestShowMedia::URL ≠ "" and refTestShowMedia::showMedia ≠ "" ; "web" ;
Case ( testlearnReportTags::filterFind = "" ; "none" ; "tag=none" ) )
) ]
Set Variable [ $reportTable; Value:1 ]
#
Else If [ Get (LayoutTableName) = "report" ]
#REPORT IWINDOW
Set Variable [ $picture; Value:$$PictureOnReportLayout ]
Set Variable [ $fileLocation; Value:$$fileLocation ]
Set Variable [ $reportTable; Value:1 ]
End If
End If
#
#
#Clear variables that transferred information
#about a picture field on the default setup, tag
#menu, or report layout when the user clicked
#on it triggering this script.
Set Variable [ $$picture ]
Set Variable [ $$fileLocation ]
Set Variable [ $$PictureOnReportLayout ]
Set Variable [ $$defaultTestSubjecPicture ]
Set Variable [ $$defaultPrimaryNodePicture ]
#
#
#If the user clicked on a picture field that is
#empty in the tag window exit this script, unless the user is in an inventory library.
If [ $fileLocation = "tag=none"
 or
$fileLocation = "none" and $lock = 1 ]
#
#Don't bother telling user how to add a picture
#to tag, as most of the time these empt fields
#are clicked on to navigate to a tag record and
#not to add a picture to them.
// Show Custom Dialog [ Message: "Use the 'add' button above to add pictures to this tag." ]
#
#
#
#
Set Variable [ $$ReplaceMeMediaRequired ]
#
#
Exit Script [ ]
End If
#
#
#Exit any field to avoid in-use error = 301 error.
Go to Field [ ]
#
#
#
#
#
#BEGIN insert or take new picture or movie
#
#
#If there is no picture (see note) and record
#is not locked then start the insert script.
#NOTE: Calculations above deterimined that
#there is no picture internally (in the database),
#or externally on the web or hard drive.
If [ $fileLocation = "none"
//$fileLocation = "none" and Get (LayoutName) = "ReferencePictureWindowEDIT"
// or $fileLocation = "none" and Get (LayoutName) = "ReferenceSPictureWindowEDIT" ]
#
#Get variables needed to run
#the insert script below.
Set Variable [ $$picture; Value:$picture ]
Set Variable [ $$reportTable; Value:$reportTable ]
Set Variable [ $$fileLocation; Value:$fileLocation ]
Set Variable [ $$learnLayout; Value:$learnLayout ]
Set Variable [ $$referenceLayout; Value:$referenceLayout ]
#
Perform Script [ “CHUNK_insertPictureOrMovie” ]
#
#If the user canceled the media add, then exit
#this script as there is no picture to show.
If [ reference::picture = ""
 or
reference::picture = "Replace Me. Media Required" ]
Exit Script [ ]
End If
#
End If
#
#
#
#
#WHY???? Testing required!
Set Variable [ $$ReplaceMeMediaRequired ]
#
#
#END insert or take new picture or movie
#
#
#
#
#
#BEGIN display picture or movie
#
#
#REFERENCE SECTION
#
#If user is on a reference layout when they
#clicked the picture thumbnail...
If [ $referenceLayout = 1 ]
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopWhenLoadingInfoRecordReferences; Value:1 ]
If [ Get ( WindowName ) ≠ "Media" ]
New Window [ Name: "Media"; Height: 435; Width: 400; Top: Get (ScreenHeight)/4; Left: Get (ScreenWidth)/4; Style:
Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Set Zoom Level [ 100%; Camera: Back; Resolution: Full ]
End If
#
#
#If in stuff library mode just go to the reference
#picture edit window, because harddrive and
#web pictures are not allowed in stuff mode.
#Also, there is no reason to prevent user from
#editing a location picture from the tag menu.
If [ $lock = "" and TEMP::InventoryLibraryYN ≠ "" and $fileLocation = "database" and $$citationMatch ≠ "node" ]
If [ Get (LayoutTableName) = "reference" and Left ( Get (LayoutName) ; 1 ) = "l" ]
Go to Layout [ “ReferenceSTagMenusPictureWindowEDIT” (reference) ]
#
#Need to know this keyword information just
#in case the user changes while in this picture
#window. If they do, the Tag Menus window
#will need to be re-sorted to show the new
#location keyword group the user put this
#Reference/Location record in.
Set Variable [ $$locationKeyword; Value:reference::kkeywordPrimary ]
#
#Go to reference edit picture layout if in the
#Reference section for a stuff/inventory library.
Else If [ Get (LayoutTableName) = "reference" and Left ( Get (LayoutName) ; 1 ) = "r" ]
Go to Layout [ “ReferenceSPictureWindowEDIT” (reference) ]
#
#Go the view layout if the above two
#if statements are not true.
Else
Go to Layout [ “ReferenceSPictureWindow” (reference) ]
End If
#
#
#UNLESS ... the user is locked, or on
#the node tag menu.
Else If [ $lock ≠ "" and TEMP::InventoryLibraryYN ≠ "" and $fileLocation = "database"
 or
$$citationMatch = "node" and TEMP::InventoryLibraryYN ≠ "" and $fileLocation = "database" ]
Go to Layout [ “ReferenceSPictureWindow” (reference) ]
#
#Inform user if the picture record was created
#while in reference mode versus stuff mode,
#and how to edit it.
Else If [ TEMP::InventoryLibraryYN ≠ "" and $fileLocation = "harddrive" ]
Go to Layout [ “ReferencePictureWindow_HDD” (reference) ]
Show Custom Dialog [ Message: "This library is set to remember things. When it was set to remember ideas, a link to this
harddrive media was added to it. If you need to edit this link, you must do so in idea mode."; Default Button: “OK”,
Commit: “Yes” ]
Show Custom Dialog [ Message: "To switch back to idea mode 1) click the 'back' buttons in the media and main windows. 2)
On the main screen, click the checkbox next to 'idea library'."; Default Button: “OK”, Commit: “Yes” ]
Else If [ TEMP::InventoryLibraryYN ≠ "" and $fileLocation = "web" ]
Go to Layout [ “ReferencePictureWindow_Web” (reference) ]
Show Custom Dialog [ Message: "This library is set to remember things. When it was set to remember ideas, a link to this
web media was added to it. If you need to edit this link, you must do so in idea mode."; Default Button: “OK”, Commit:
“Yes” ]
Show Custom Dialog [ Message: "To switch back to idea mode 1) click the 'back' buttons in the media and main windows. 2)
On the main screen, click the checkbox next to 'idea library'."; Default Button: “OK”, Commit: “Yes” ]
#
#
#If in reference library mode determine the
#where the media file is located and display it in
#on the correct layout.
#
#Display database file.
Else If [ TEMP::InventoryLibraryYN = "" ]
#
#Go to edit media layout only if on the
#referenceEDIT layout, and the node
#that created the referenced hasn't
#locked it.
If [ $fileLocation = "database" ]
If [ $referenceEDIT = 1 and $lock = "" ]
Go to Layout [ “ReferencePictureWindowEDIT” (reference) ]
Else
Go to Layout [ “ReferencePictureWindow” (reference) ]
End If
#
#Display harddrive file.
Else If [ $fileLocation = "harddrive" ]
If [ $referenceEDIT = 1 and $lock = "" ]
Go to Layout [ “ReferencePictureWindow_HDDEDIT” (reference) ]
Else
Go to Layout [ “ReferencePictureWindow_HDD” (reference) ]
End If
#
#Display webpage.
Else If [ $fileLocation = "web" ]
If [ $referenceEDIT = 1 and $lock = "" ]
Go to Layout [ “ReferencePictureWindow_WebEDIT” (reference) ]
Else
Go to Layout [ “ReferencePictureWindow_Web” (reference) ]
End If
End If
End If
#
#Show only the record of interest.
Enter Find Mode [ ]
Set Field [ reference::_Lreference; $picture ]
Perform Find [ ]
#
#If picture is of a locked copyright image,
#then go to view only layout. This layout
#check is needed if the user happens to be in
#inventory mode on the Setup copyright
#layout, where it is essential that a full
#reference library reference is shown
#versus the inventory library reference.
If [ reference::lock = "lock"
 or
$$citationMatch = "copyright" and $$add ≠ "" ]
Go to Layout [ “ReferencePictureWindow” (reference) ]
// Else If [ $$add ≠ "" ]
// Go to Layout [ “ReferenceSPictureWindow” (reference) ]
End If
#
#
#Turn back on the record load variables and
#pause the script to allow the user the
#opportunity to look at the media. Pausing will
#prevent the user from doing anything else until
#they are finished and close the media window.
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopWhenLoadingInfoRecordReferences ]
#Resize window so it is compatible with the
#pictureViewButton script's window sizes.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Move/Resize Window [ Current Window; Height: 435; Width: 400; Top: Get (ScreenHeight) / 4; Left: Get (ScreenWidth) / 4 ]
Else
Move/Resize Window [ Current Window; Height: 395; Width: 400; Top: Get (ScreenHeight) / 4; Left: Get (ScreenWidth) / 4 ]
End If
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
#
#
End If
#
#REFERENCE SECTION
#
#
#LEARN SECTION
#
#NOTE: Learn records can display both
#referenced reference record's media
#as well as their own media.
#
#If user is on a testlearn table layout when they
#clicked the picture thumbnail...
If [ Get (LayoutTableName) = "testLearn" or Get (LayoutTableName) = "testlearnReportTags" or Get (LayoutTableName) = "report" ]
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stoploadtestinfo; Value:1 ]
Set Variable [ $$stopLoadTestRecord; Value:1 ]
Set Variable [ $learnWindowName; Value:Get ( WindowName ) ]
New Window [ Name: "Media"; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get
(ScreenWidth)/4; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Set Zoom Level [ 100%; Camera: Back; Resolution: Full ]
#
#
#Go to edit media layout only if on a
#Learn window layout, and the node
#that created the learn record hasn't
#locked it.
If [ $lock = "" and testlearnReportTags::filterFind = "" and tagTLNodePrimary::orderOrLock = "" and tagTLReportNodePrimary::
orderOrLock = "" and Get (LayoutName) ≠ "PrintReportEdit" ]
#
#Display database file.
If [ $fileLocation = "database" or $fileLocation = "TLpicture" ]
If [ $fileLocation = "database" ]
#
#If looking at learn media in the tag menus
#window, go to the view layout.
If [ $learnWindowName = "Tag Menus" and Get ( LayoutTableName ) = "testlearn" ]
Go to Layout [ “LearnRefPictureWindow” (testlearn) ]
Else
Go to Layout [ “LearnRefPictureWindowEDIT” (testlearn) ]
End If
Else If [ $fileLocation = "TLpicture" ]
#
#If looking at learn media in the tag menus
#window, go to the view layout.
If [ $learnWindowName = "Tag Menus" and Get ( LayoutTableName ) = "testlearn" ]
Go to Layout [ “LearnPictureWindow” (testlearn) ]
Else
Go to Layout [ “LearnPictureWindowEDIT” (testlearn) ]
End If
End If
#
#Display harddrive file.
Else If [ $fileLocation = "harddrive" ]
#
#If looking at learn media in the tag menus
#window, go to the view layout.
If [ $learnWindowName = "Tag Menus" and Get ( LayoutTableName ) = "testlearn" ]
Go to Layout [ “LearnRefExternalPictureWindow” (testlearn) ]
Else
Go to Layout [ “LearnRefExternalPictureWindowEDIT” (testlearn) ]
End If
#
#Display webpage.
Else If [ $fileLocation = "web" ]
#
#If looking at learn media in the tag menus
#window, go to the view layout.
If [ $learnWindowName = "Tag Menus" and Get ( LayoutTableName ) = "testlearn" ]
Go to Layout [ “LearnRefWebPictureWindow” (testlearn) ]
Else
Go to Layout [ “LearnRefWebPictureWindowEDIT” (testlearn) ]
End If
End If
#
#Not editable (view only) layouts.
Else If [ $lock ≠ "" or $reportTable ≠ "" or tagTLNodePrimary::orderOrLock ≠ "" or tagTLReportNodePrimary::orderOrLock ≠ "" or
Get (LayoutName) = "PrintReportEdit" // or Right ( Get (LayoutName) ; 4 ) = "info" ]
#
#Display database file.
If [ $fileLocation = "database" or $fileLocation = "TLpicture" ]
If [ $fileLocation = "database" ]
Go to Layout [ “LearnRefPictureWindow” (testlearn) ]
Else If [ $fileLocation = "TLpicture" ]
Go to Layout [ “LearnPictureWindow” (testlearn) ]
End If
#
#Display harddrive file.
Else If [ $fileLocation = "harddrive" ]
Go to Layout [ “LearnRefExternalPictureWindow” (testlearn) ]
#
#Display webpage.
Else If [ $fileLocation = "web" ]
Go to Layout [ “LearnRefWebPictureWindow” (testlearn) ]
End If
End If
#
#Show only the record of interest.
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $picture ]
Perform Find [ ]
#
#Turn back on the record load variables and
#pause the script to allow the user the
#opportunity to look at the media. Pausing will
#prevent the user from doing anything else until
#they are finished and close the media window.
Set Variable [ $$stoploadtestinfo ]
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTestRecord ]
#Resize window so it is compatible with the
#pictureViewButton script's window sizes.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Move/Resize Window [ Current Window; Height: 435; Width: 400; Top: Get (ScreenHeight) / 4; Left: Get (ScreenWidth) / 4 ]
Else
Move/Resize Window [ Current Window; Height: 395; Width: 400; Top: Get (ScreenHeight) / 4; Left: Get (ScreenWidth) / 4 ]
End If
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
#
End If
#
#LEARN SECTION
#
