pictures: showCitationPicture1inNewWindow
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Not sure why I decided lock this, but it seems user
#can't do anything to data by viewing pictures so I
#disabled the lock steps below.
// #If node is currenlty locked then stop script, inform user.
// If [ tagTLNodePrimary::orderOrLock ≠ "" ]
// Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the
password to unlock it, then you will able to add pictures to records assigned to this node."; Buttons: “OK” ]
// Exit Script [ ]
// End If
#
#iDEVICES not tested using this script since v3.1 udpate!!!!!
#Determine where picture or movie is located
#on iPhone and iPads.
If [ PatternCount ( Get ( ApplicationVersion ) ; "GO" ) ]
Set Variable [ $$stopLoadCitation; Value:1 ]
New Window [ Name: " "; Height: Get (ScreenHeight); Width: Get (ScreenWidth); Top: 0; Left: 0 ]
#
If [ Get (LayoutTableName) = "reference" ]
Go to Layout [ “ReferencePictureWindow” (reference) ]
#
Else If [ Get (LayoutTableName) = "testlearn" ]
Go to Layout [ “LearnPictureWindow” (testlearn) ]
#
Else If [ Get (LayoutTableName) = "testlearnReportTags" ]
#
#Because there is no testlearnReportTags
#picture layout, capture the ID for this record
#so it can be found on the testlearn picture layout.
Set Variable [ $testlearnReportTagsID; Value:testlearnReportTags::_Ltestlearn ]
#
#Find this record for the testlearn layout.
Go to Layout [ “LearnPictureWindow” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $testlearnReportTagsID ]
Perform Find [ ]
End If
#
Set Variable [ $$stopLoadCitation ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
End If
#
#
#
#BEGIN NOTE: Test layouts have no pictures,
#so this section of code is not in use.
#
#Determine where picture or movie is located
#on the reference window and then open it.
If [ Get ( LayoutTableName ) = "test" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
// Go to Field [ reference::picture ]
// Go to Field [ ]
// #
// New Window [ Name: reference::picture; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4;
Left: Get (ScreenWidth)/4 ]
// Go to Layout [ “ReferencePictureWindow” (reference) ]
Insert Picture [ ]
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
End If
#
#END NOTE: Test layouts have no pictures,
#so this section of code is not in use.
#
#
#
#Determine where picture or movie is located
#on the reference window and then open it.
If [ reference::picture ≠ ""
or reference::kfileLocation ≠ ""
or reference::URL ≠ "" and reference::showMedia ≠ ""
 // and Get (LayoutName) ≠ "ReferenceEDIT" ]
If [ reference::picture ≠ "" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Field [ reference::picture ]
Go to Field [ ]
#
New Window [ Name: " "; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get
(ScreenWidth)/4 ]
If [ Get (LayoutName) = "ReferenceEDIT" or Get (LayoutName) = "ReferenceEDITstuff" ]
Go to Layout [ “ReferencePictureWindowEDIT” (reference) ]
Else
Go to Layout [ “ReferencePictureWindow” (reference) ]
End If
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
Else If [ FilterValues ( reference::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & reference::fileName ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & reference::fileName ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( reference::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & reference::fileName ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & reference::fileName ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( reference::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagRefFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( reference::fileName ; 1 ) = "/" ; Substitute ( reference::fileName ; " " ; "%20" ) ;
 "/" & Substitute ( reference::fileName ; " " ; "%20" ) ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagRefFolderPath::tag ; " " ; " " ) &
Case ( Left ( reference::fileName ; 1 ) = "/" ; Substitute ( reference::fileName ; " " ; " " ) ;
 "/" & Substitute ( reference::fileName ; " " ; " " ) ) ]
[ No dialog ]
Exit Script [ ]
Else If [ reference::URL ≠ "" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Field [ reference::picture ]
Go to Field [ ]
#
New Window [ Name: " "; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get
(ScreenWidth)/4 ]
If [ Get (LayoutName) = "ReferenceEDIT" or Get (LayoutName) = "ReferenceEDITstuff" ]
Go to Layout [ “ReferencePictureWindowEDIT” (reference) ]
Else
Go to Layout [ “ReferencePictureWindow” (reference) ]
End If
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
Open URL [ reference::URL ]
[ No dialog ]
Exit Script [ ]
End If
End If
#
#Determine where reference picture or movie is located
#on the tag menus window and then open it.
If [ citationPicture1::picture ≠ ""
or citationPicture1::kfileLocation ≠ ""
or citationPicture1::URL ≠ "" ]
If [ citationPicture1::picture ≠ "" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $picture; Value:tagMenus::Kpicture1 ]
Go to Field [ ]
#
New Window [ Name: " "; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get
(ScreenWidth)/4 ]
Go to Layout [ “ReferencePictureWindow” (reference) ]
#
Enter Find Mode [ ]
Set Field [ reference::_Lreference; $picture ]
Perform Find [ ]
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
Else If [ FilterValues ( citationPicture1::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citationPicture1::fileName ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citationPicture1::fileName ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citationPicture1::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & citationPicture1::fileName ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & citationPicture1::fileName ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citationPicture1::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagPathPicture1_button::tag ; " " ; "%20" ) &
Case ( Left ( citationPicture1::fileName ; 1 ) = "/" ; Substitute ( citationPicture1::fileName ; " " ; "%20" ) ;
 "/" & Substitute ( citationPicture1::fileName ; " " ; "%20" ) ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagPathPicture1_button::tag ; " " ; " " ) &
Case ( Left ( citationPicture1::fileName ; 1 ) = "/" ; Substitute ( citationPicture1::fileName ; " " ; " " ) ;
 "/" & Substitute ( citationPicture1::fileName ; " " ; " " ) ) ]
[ No dialog ]
Exit Script [ ]
Else If [ citationPicture1::URL ≠ "" ]
#
#
If [ citationPicture1::showMedia ≠ "" ]
Set Variable [ $$stopLoadCitation; Value:1 ]
Set Variable [ $picture; Value:tagMenus::Kpicture1 ]
Go to Field [ ]
#
New Window [ Name: ""; Height: Get (ScreenHeight); Width: Get (ScreenWidth); Top: 0; Left: 0 ]
Go to Layout [ “ReferencePictureWindow” (reference) ]
#
Enter Find Mode [ ]
Set Field [ reference::_Lreference; $picture ]
Perform Find [ ]
#
Set Variable [ $$stopLoadCitation ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
End If
#
Open URL [ Substitute ( citationPicture1::URL ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
End If
End If
#
#Determine where testlearn picture or movie is located
#on the tag menus window and then open it.
If [ TLPicture1::Picture ≠ ""
or TLPicture1::kfileLocation ≠ ""
or TLPicture1::URL ≠ "" ]
If [ TLPicture1::Picture ≠ "" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $picture; Value:tagMenus::Kpicture1 ]
Go to Field [ ]
#
New Window [ Name: " "; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get
(ScreenWidth)/4 ]
Go to Layout [ “LearnPictureWindow” (testlearn) ]
#
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $picture ]
Perform Find [ ]
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
Else If [ FilterValues ( TLPicture1::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & TLPicture1::filename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & TLPicture1::filename ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( TLPicture1::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & TLPicture1::filename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & TLPicture1::filename ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( TLPicture1::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagTLPathPicture1_button::tag ; " " ; "%
20" ) &
Case ( Left ( TLPicture1::filename ; 1 ) = "/" ; Substitute ( TLPicture1::filename ; " " ; "%20" ) ;
 "/" & Substitute ( TLPicture1::filename ; " " ; "%20" ) ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagTLPathPicture1_button::tag ; " " ; " " ) &
Case ( Left ( TLPicture1::filename ; 1 ) = "/" ; Substitute ( TLPicture1::filename ; " " ; " " ) ;
 "/" & Substitute ( TLPicture1::filename ; " " ; " " ) ) ]
[ No dialog ]
Exit Script [ ]
Else If [ TLPicture1::URL ≠ "" ]
Open URL [ Substitute ( TLPicture1::URL ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
End If
End If
#
#Determine where testlearn picture or movie is located
#on testlearn Layout and then open it.
If [ testlearn::Picture ≠ ""
or testlearn::kfileLocation ≠ ""
or testlearn::URL ≠ ""
or testlearn::kshowReferencedMedia ≠ "" ]
If [ testlearn::Picture ≠ "" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Field [ ]
#
New Window [ Name: " "; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get
(ScreenWidth)/4 ]
Go to Layout [ “LearnPictureWindow” (testlearn) ]
Go to Field [ testlearn::Picture ]
Go to Field [ ]
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
#
Else If [ FilterValues ( testlearn::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & testlearn::filename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & testlearn::filename ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( testlearn::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & testlearn::filename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & testlearn::filename ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( testlearn::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagTLFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( testlearn::filename ; 1 ) = "/" ; Substitute ( testlearn::filename ; " " ; "%20" ) ;
 "/" & Substitute ( testlearn::filename ; " " ; "%20" ) ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagTLFolderPath::tag ; " " ; " " ) &
Case ( Left ( testlearn::filename ; 1 ) = "/" ; Substitute ( testlearn::filename ; " " ; " " ) ;
 "/" & Substitute ( testlearn::filename ; " " ; " " ) ) ]
[ No dialog ]
Exit Script [ ]
#
Else If [ testlearn::URL ≠ "" or
testlearn::kshowReferencedMedia ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Field [ ]
#
New Window [ Name: " "; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get
(ScreenWidth)/4 ]
Go to Layout [ “LearnPictureWindow” (testlearn) ]
Go to Field [ testlearn::Picture ]
End If
Go to Field [ ]
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
#
// Else If [ testlearn::URL ≠ "" ]
// Open URL [ Substitute ( testlearn::URL ; " " ; "%20" ) ]
[ No dialog ]
// Exit Script [ ]
// End If
End If
#
#Determine where testlearn picture or movie is located
#on testlearnDiscoveryTag Layout and then open it.
#
#Because there is no testlearnReportTags
#picture layout, capture the ID for this record
#so it can be found on the testlearn picture layout.
Set Variable [ $testlearnReportTagsID; Value:testlearnReportTags::_Ltestlearn ]
#
If [ testlearnReportTags::Picture ≠ ""
or testlearnReportTags::kfileLocation ≠ ""
or testlearnReportTags::URL ≠ ""
or testlearnReportTags::kshowReferencedMedia ≠ "" ]
If [ testlearnReportTags::Picture ≠ "" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Field [ ]
#
New Window [ Name: " "; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get
(ScreenWidth)/4 ]
Go to Layout [ “LearnPictureWindow” (testlearn) ]
#
#Find this record for the testlearn layout.
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $testlearnReportTagsID ]
Perform Find [ ]
#
Go to Field [ testlearn::Picture ]
Go to Field [ ]
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
#
Else If [ testlearnReportTags::URL ≠ "" or
testlearnReportTags::kshowReferencedMedia ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Field [ ]
#
New Window [ Name: " "; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get
(ScreenWidth)/4 ]
Go to Layout [ “LearnPictureWindow” (testlearn) ]
#
#Find this record for the testlearn layout.
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $testlearnReportTagsID ]
Perform Find [ ]
#
Go to Field [ testlearn::Picture ]
End If
Go to Field [ ]
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
#
#Since version 2 the file path media option has
#been disabled. If that changes, then these
#script steps become useful.
// Else If [ FilterValues ( testlearn::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & testlearn::filename ; " " ; "%20" ) ]
[ No dialog ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & testlearn::filename ; " " ; " " ) ]
[ No dialog ]
// Exit Script [ ]
// Else If [ FilterValues ( testlearn::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & testlearn::filename ; " " ; "%20" ) ]
[ No dialog ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & testlearn::filename ; " " ; " " ) ]
[ No dialog ]
// Exit Script [ ]
// Else If [ FilterValues ( testlearn::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagTLFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( testlearn::filename ; 1 ) = "/" ; Substitute ( testlearn::filename ; " " ; "%20" ) ;
 "/" & Substitute ( testlearn::filename ; " " ; "%20" ) ) ]
[ No dialog ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagTLFolderPath::tag ; " " ; " " ) &
Case ( Left ( testlearn::filename ; 1 ) = "/" ; Substitute ( testlearn::filename ; " " ; " " ) ;
 "/" & Substitute ( testlearn::filename ; " " ; " " ) ) ]
[ No dialog ]
// Exit Script [ ]
// Else If [ testlearn::URL ≠ "" ]
// Open URL [ Substitute ( testlearn::URL ; " " ; "%20" ) ]
[ No dialog ]
// Exit Script [ ]
// End If
End If
#
#Determine where default picture or movie is located
#on default setup Layout and then open it.
If [ defaultPictureRef::picture ≠ ""
or defaultPictureRef::kfileLocation ≠ ""
or defaultPictureRef::URL ≠ "" ]
If [ defaultPictureRef::picture ≠ "" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $picture; Value:defaultPictureRef::_Lreference ]
Go to Field [ ]
#
New Window [ Name: " "; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get
(ScreenWidth)/4 ]
Go to Layout [ “ReferencePictureWindow” (reference) ]
#
Enter Find Mode [ ]
Set Field [ reference::_Lreference; $picture ]
Pause/Resume Script [ Indefinitely ]
Perform Find [ ]
#
Set Variable [ $$stoploadCitation ]
Exit Script [ ]
Else If [ FilterValues ( defaultPictureRef::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & defaultPictureRef::fileName ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & defaultPictureRef::fileName ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( defaultPictureRef::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & defaultPictureRef::fileName ; " " ; " " ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & defaultPictureRef::fileName ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( defaultPictureRef::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagDefaultFolderPathRef::tag ; " " ; "%20" )
&
Case ( Left ( defaultPictureRef::fileName ; 1 ) = "/" ; Substitute ( defaultPictureRef::fileName ; " " ; "%20" ) ;
 "/" & Substitute ( defaultPictureRef::fileName ; " " ; "%20" ) ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagDefaultFolderPathRef::tag ; " " ; " " ) &
Case ( Left ( defaultPictureRef::fileName ; 1 ) = "/" ; Substitute ( defaultPictureRef::fileName ; " " ; " " ) ;
 "/" & Substitute ( defaultPictureRef::fileName ; " " ; " " ) ) ]
[ No dialog ]
Exit Script [ ]
Else If [ defaultPictureRef::URL ≠ "" ]
Open URL [ Substitute ( defaultPictureRef::URL ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
End If
Else If [ defaultPictureTL::Picture ≠ ""
or defaultPictureTL::kfileLocation ≠ ""
or defaultPictureTL::URL ≠ "" ]
If [ defaultPictureTL::Picture ≠ "" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $picture; Value:defaultPictureTL::_Ltestlearn ]
Go to Field [ ]
#
New Window [ Name: " "; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get
(ScreenWidth)/4 ]
Go to Layout [ “LearnPictureWindow” (testlearn) ]
#
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $picture ]
Pause/Resume Script [ Indefinitely ]
Perform Find [ ]
#
Set Variable [ $$stoploadCitation ]
Exit Script [ ]
Else If [ FilterValues ( defaultPictureTL::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & defaultPictureTL::filename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & defaultPictureTL::filename ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( defaultPictureTL::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & defaultPictureTL::filename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 9) & defaultPictureTL::filename ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( defaultPictureTL::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagDefaultFolderPathTL::tag ; " " ; "%20" )
&
Case ( Left ( defaultPictureTL::filename ; 1 ) = "/" ; Substitute ( defaultPictureTL::filename ; " " ; "%20" ) ;
 "/" & Substitute ( defaultPictureTL::filename ; " " ; "%20" ) ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagDefaultFolderPathTL::tag ; " " ; " " ) &
Case ( Left ( defaultPictureTL::filename ; 1 ) = "/" ; Substitute ( defaultPictureTL::filename ; " " ; " " ) ;
 "/" & Substitute ( defaultPictureTL::filename ; " " ; " " ) ) ]
[ No dialog ]
Exit Script [ ]
Else If [ defaultPictureTL::URL ≠ "" ]
Open URL [ Substitute ( defaultPictureTL::URL ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
End If
End If
#
#If there is no file found then ask user what picture
#to insert.
If [ Get (LayoutTableName) = "reference" and Get ( WindowName ) ≠ "Tag Menus" ]
Go to Field [ reference::picture ]
Show Custom Dialog [ Message: "Select a picture or movie to insert."; Buttons: “cancel”, “picture”, “movie” ]
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Insert Picture [ ]
Go to Field [ ]
Else If [ Get ( LastMessageChoice ) = 3 ]
Insert QuickTime [ ]
Go to Field [ ]
End If
Go to Field [ ]
Else If [ Get (LayoutTableName) = "testlearn" and Get ( WindowName ) ≠ "Tag Menus" ]
Go to Field [ testlearn::Picture ]
Show Custom Dialog [ Message: "Select a picture or movie to insert."; Buttons: “cancel”, “picture”, “movie” ]
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Insert Picture [ ]
Go to Field [ ]
Else If [ Get ( LastMessageChoice ) = 3 ]
Insert QuickTime [ ]
Go to Field [ ]
End If
Go to Field [ ]
Else If [ Get (LayoutTableName) = "testlearnReportTags" and Get ( WindowName ) = "Tag Menus" ]
Go to Field [ testlearnReportTags::Picture ]
Show Custom Dialog [ Message: "Select a picture or movie to insert."; Buttons: “cancel”, “picture”, “movie” ]
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Insert Picture [ ]
Go to Field [ ]
Else If [ Get ( LastMessageChoice ) = 3 ]
Insert QuickTime [ ]
Go to Field [ ]
End If
Go to Field [ ]
End If
December 27, ଘ౮27 18:42:57 Library.fp7 - showCitationPicture1inNewWindow -1-
