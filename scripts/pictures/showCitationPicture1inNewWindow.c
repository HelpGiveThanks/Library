pictures: showCitationPicture1inNewWindow
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Not sure why I decided lock this, but it seems user
#can't do anything to data by viewing pictures so I
#disabled the lock steps below.
// #If node is currenlty locked then stop script, inform user.
// If [ tagTLNodePrimary::orderOrLock ≠ "" ]
// Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the password to unlock it, then you will able to add pictures to records assigned to this node."; Buttons: “OK” ]
// Exit Script [ ]
// End If
#
#Determine where picture or movie is located
If [ PatternCount ( Get ( ApplicationVersion ) ; "GO" ) ]
Set Variable [ $$stopLoadCitation; Value:1 ]
New Window [ Height: Get (ScreenHeight); Width: Get (ScreenWidth); Top: 0; Left: 0 ]
If [ Get (LayoutTableName) = "reference" ]
Go to Layout [ “ReferencePictureWindow” (reference) ]
Else If [ Get (LayoutTableName) = "testlearn" or Get (LayoutTableName) = "testlearnReportTags" ]
Go to Layout [ “LearnPictureWindow” (testlearn) ]
End If
Set Variable [ $$stopLoadCitation ]
Exit Script [ ]
End If
#
#Determine where picture or movie is located
#on the reference window and then open it.
If [ Get ( LayoutTableName ) = "test" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
// Go to Field [ reference::picture ]
// Go to Field [ ]
// #
// New Window [ Name: reference::picture; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get (ScreenWidth)/4 ]
// Go to Layout [ “ReferencePictureWindow” (reference) ]
Insert Picture [ ]
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
End If
#
#Determine where picture or movie is located
#on the reference window and then open it.
If [ reference::picture ≠ ""
or reference::kfileLocation ≠ ""
or reference::URL ≠ "" and Get (LayoutName) ≠ "ReferenceEDIT" ]
If [ reference::picture ≠ "" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Field [ reference::picture ]
Go to Field [ ]
#
New Window [ Name: reference::picture; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get (ScreenWidth)/4 ]
Go to Layout [ “ReferencePictureWindow” (reference) ]
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
Else If [ FilterValues ( reference::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & reference::fileName ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & reference::fileName ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( reference::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & reference::fileName ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & reference::fileName ; " " ; " " ) ]
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
New Window [ Name: citationPicture1::picture; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get (ScreenWidth)/4 ]
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
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citationPicture1::fileName ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citationPicture1::fileName ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citationPicture1::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & citationPicture1::fileName ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & citationPicture1::fileName ; " " ; " " ) ]
[ No dialog ]
January 7, 平成26 17:17:04 Imagination Quality Management.fp7 - showCitationPicture1inNewWindow -1-pictures: showCitationPicture1inNewWindow
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
New Window [ Name: TLPicture1::Picture; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get (ScreenWidth)/4 ]
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
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & TLPicture1::filename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & TLPicture1::filename ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( TLPicture1::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & TLPicture1::filename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & TLPicture1::filename ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( TLPicture1::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagTLPathPicture1_button::tag ; " " ; "%20" ) &
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
or testlearn::URL ≠ "" ]
If [ testlearn::Picture ≠ "" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Field [ ]
#
New Window [ Name: testlearn::Picture; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get (ScreenWidth)/4 ]
Go to Layout [ “LearnPictureWindow” (testlearn) ]
Go to Field [ testlearn::Picture ]
Go to Field [ ]
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
#
Else If [ FilterValues ( testlearn::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & testlearn::filename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & testlearn::filename ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( testlearn::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & testlearn::filename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & testlearn::filename ; " " ; " " ) ]
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
Else If [ testlearn::URL ≠ "" ]
Open URL [ Substitute ( testlearn::URL ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
End If
End If
#
#Determine where testlearn picture or movie is located
#on testlearnDiscoveryTag Layout and then open it.
If [ testlearnReportTags::Picture ≠ ""
//or testlearnReportTags::kfileLocation ≠ ""
//or testlearnReportTags::URL ≠ "" ]
January 7, 平成26 17:17:04 Imagination Quality Management.fp7 - showCitationPicture1inNewWindow -2-pictures: showCitationPicture1inNewWindow If [ testlearnReportTags::Picture ≠ ""
//or testlearnReportTags::kfileLocation ≠ ""
//or testlearnReportTags::URL ≠ "" ]
If [ testlearnReportTags::Picture ≠ "" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Field [ ]
#
Close Window [ Name: "Discovery Picture"; Current file ]
New Window [ Name: "Discovery Picture"; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get (ScreenWidth)/4 ]
Go to Layout [ “reportPictureWindow” (testlearnReportTags) ]
Go to Field [ testlearnReportTags::Picture ]
Go to Field [ ]
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
#
// Else If [ FilterValues ( testlearn::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & testlearn::filename ; " " ; "%20" ) ]
[ No dialog ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & testlearn::filename ; " " ; " " ) ]
[ No dialog ]
// Exit Script [ ]
// Else If [ FilterValues ( testlearn::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & testlearn::filename ; " " ; "%20" ) ]
[ No dialog ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & testlearn::filename ; " " ; " " ) ]
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
End If
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
New Window [ Name: defaultPictureRef::picture; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get (ScreenWidth)/4 ]
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
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & defaultPictureRef::fileName ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & defaultPictureRef::fileName ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( defaultPictureRef::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & defaultPictureRef::fileName ; " " ; " " ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & defaultPictureRef::fileName ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( defaultPictureRef::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagDefaultFolderPathRef::tag ; " " ; "%20" ) &
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
New Window [ Name: defaultPictureTL::Picture; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get (ScreenWidth)/4 ]
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
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & defaultPictureTL::filename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & defaultPictureTL::filename ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( defaultPictureTL::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
January 7, 平成26 17:17:04 Imagination Quality Management.fp7 - showCitationPicture1inNewWindow -3-pictures: showCitationPicture1inNewWindow
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & defaultPictureTL::filename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & defaultPictureTL::filename ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( defaultPictureTL::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagDefaultFolderPathTL::tag ; " " ; "%20" ) &
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
Show Custom Dialog [ Message: "Select a picture to insert. "; Buttons: “OK” ]
Insert Picture [ ]
Go to Field [ ]
Else If [ Get (LayoutTableName) = "testlearn" and Get ( WindowName ) ≠ "Tag Menus" ]
Go to Field [ testlearn::Picture ]
Show Custom Dialog [ Message: "Select a picture to insert. "; Buttons: “OK” ]
Insert Picture [ ]
Go to Field [ ]
Else If [ Get (LayoutTableName) = "testlearnReportTags" ]
Close Window [ Name: "Discovery Picture"; Current file ]
New Window [ Name: "Discovery Picture"; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get (ScreenWidth)/4 ]
Go to Layout [ “reportPictureWindow” (testlearnReportTags) ]
Go to Field [ testlearnReportTags::Picture ]
Show Custom Dialog [ Message: "Select a picture to insert. "; Buttons: “OK” ]
Insert Picture [ ]
Go to Field [ ]
Go to Field [ ]
End If
January 7, 平成26 17:17:04 Imagination Quality Management.fp7 - showCitationPicture1inNewWindow -4-
