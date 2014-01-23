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
Pause/Resume Script [ Indeﬁnitely ]
Exit Script [ ]
End If
#
#Determine where picture or movie is located
#on the reference window and then open it.
If [ reference::picture ≠ ""
or reference::kﬁleLocation ≠ ""
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
Pause/Resume Script [ Indeﬁnitely ]
Exit Script [ ]
Else If [ FilterValues ( reference::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & reference::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & reference::ﬁleName ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( reference::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & reference::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & reference::ﬁleName ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( reference::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagRefFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( reference::ﬁleName ; 1 ) = "/" ; Substitute ( reference::ﬁleName ; " " ; "%20" ) ;
 "/" & Substitute ( reference::ﬁleName ; " " ; "%20" ) ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagRefFolderPath::tag ; " " ; " " ) &
Case ( Left ( reference::ﬁleName ; 1 ) = "/" ; Substitute ( reference::ﬁleName ; " " ; " " ) ;
 "/" & Substitute ( reference::ﬁleName ; " " ; " " ) ) ]
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
or citationPicture1::kﬁleLocation ≠ ""
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
Pause/Resume Script [ Indeﬁnitely ]
Exit Script [ ]
Else If [ FilterValues ( citationPicture1::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citationPicture1::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citationPicture1::ﬁleName ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citationPicture1::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & citationPicture1::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & citationPicture1::ﬁleName ; " " ; " " ) ]
[ No dialog ]
January 7, 平成26 17:17:04 Imagination Quality Management.fp7 - showCitationPicture1inNewWindow -1-pictures: showCitationPicture1inNewWindow
Exit Script [ ]
Else If [ FilterValues ( citationPicture1::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagPathPicture1_button::tag ; " " ; "%20" ) &
Case ( Left ( citationPicture1::ﬁleName ; 1 ) = "/" ; Substitute ( citationPicture1::ﬁleName ; " " ; "%20" ) ;
 "/" & Substitute ( citationPicture1::ﬁleName ; " " ; "%20" ) ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagPathPicture1_button::tag ; " " ; " " ) &
Case ( Left ( citationPicture1::ﬁleName ; 1 ) = "/" ; Substitute ( citationPicture1::ﬁleName ; " " ; " " ) ;
 "/" & Substitute ( citationPicture1::ﬁleName ; " " ; " " ) ) ]
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
or TLPicture1::kﬁleLocation ≠ ""
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
Pause/Resume Script [ Indeﬁnitely ]
Exit Script [ ]
Else If [ FilterValues ( TLPicture1::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & TLPicture1::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & TLPicture1::ﬁlename ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( TLPicture1::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & TLPicture1::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & TLPicture1::ﬁlename ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( TLPicture1::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagTLPathPicture1_button::tag ; " " ; "%20" ) &
Case ( Left ( TLPicture1::ﬁlename ; 1 ) = "/" ; Substitute ( TLPicture1::ﬁlename ; " " ; "%20" ) ;
 "/" & Substitute ( TLPicture1::ﬁlename ; " " ; "%20" ) ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagTLPathPicture1_button::tag ; " " ; " " ) &
Case ( Left ( TLPicture1::ﬁlename ; 1 ) = "/" ; Substitute ( TLPicture1::ﬁlename ; " " ; " " ) ;
 "/" & Substitute ( TLPicture1::ﬁlename ; " " ; " " ) ) ]
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
or testlearn::kﬁleLocation ≠ ""
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
Pause/Resume Script [ Indeﬁnitely ]
Exit Script [ ]
#
Else If [ FilterValues ( testlearn::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & testlearn::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & testlearn::ﬁlename ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( testlearn::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & testlearn::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & testlearn::ﬁlename ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( testlearn::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagTLFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( testlearn::ﬁlename ; 1 ) = "/" ; Substitute ( testlearn::ﬁlename ; " " ; "%20" ) ;
 "/" & Substitute ( testlearn::ﬁlename ; " " ; "%20" ) ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagTLFolderPath::tag ; " " ; " " ) &
Case ( Left ( testlearn::ﬁlename ; 1 ) = "/" ; Substitute ( testlearn::ﬁlename ; " " ; " " ) ;
 "/" & Substitute ( testlearn::ﬁlename ; " " ; " " ) ) ]
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
//or testlearnReportTags::kﬁleLocation ≠ ""
//or testlearnReportTags::URL ≠ "" ]
January 7, 平成26 17:17:04 Imagination Quality Management.fp7 - showCitationPicture1inNewWindow -2-pictures: showCitationPicture1inNewWindow If [ testlearnReportTags::Picture ≠ ""
//or testlearnReportTags::kﬁleLocation ≠ ""
//or testlearnReportTags::URL ≠ "" ]
If [ testlearnReportTags::Picture ≠ "" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Field [ ]
#
Close Window [ Name: "Discovery Picture"; Current ﬁle ]
New Window [ Name: "Discovery Picture"; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get (ScreenWidth)/4 ]
Go to Layout [ “reportPictureWindow” (testlearnReportTags) ]
Go to Field [ testlearnReportTags::Picture ]
Go to Field [ ]
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indeﬁnitely ]
Exit Script [ ]
#
// Else If [ FilterValues ( testlearn::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & testlearn::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & testlearn::ﬁlename ; " " ; " " ) ]
[ No dialog ]
// Exit Script [ ]
// Else If [ FilterValues ( testlearn::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & testlearn::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & testlearn::ﬁlename ; " " ; " " ) ]
[ No dialog ]
// Exit Script [ ]
// Else If [ FilterValues ( testlearn::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagTLFolderPath::tag ; " " ; "%20" ) &
Case ( Left ( testlearn::ﬁlename ; 1 ) = "/" ; Substitute ( testlearn::ﬁlename ; " " ; "%20" ) ;
 "/" & Substitute ( testlearn::ﬁlename ; " " ; "%20" ) ) ]
[ No dialog ]
// Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagTLFolderPath::tag ; " " ; " " ) &
Case ( Left ( testlearn::ﬁlename ; 1 ) = "/" ; Substitute ( testlearn::ﬁlename ; " " ; " " ) ;
 "/" & Substitute ( testlearn::ﬁlename ; " " ; " " ) ) ]
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
or defaultPictureRef::kﬁleLocation ≠ ""
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
Pause/Resume Script [ Indeﬁnitely ]
Perform Find [ ]
#
Set Variable [ $$stoploadCitation ]
Exit Script [ ]
Else If [ FilterValues ( defaultPictureRef::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & defaultPictureRef::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & defaultPictureRef::ﬁleName ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( defaultPictureRef::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & defaultPictureRef::ﬁleName ; " " ; " " ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & defaultPictureRef::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( defaultPictureRef::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagDefaultFolderPathRef::tag ; " " ; "%20" ) &
Case ( Left ( defaultPictureRef::ﬁleName ; 1 ) = "/" ; Substitute ( defaultPictureRef::ﬁleName ; " " ; "%20" ) ;
 "/" & Substitute ( defaultPictureRef::ﬁleName ; " " ; "%20" ) ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagDefaultFolderPathRef::tag ; " " ; " " ) &
Case ( Left ( defaultPictureRef::ﬁleName ; 1 ) = "/" ; Substitute ( defaultPictureRef::ﬁleName ; " " ; " " ) ;
 "/" & Substitute ( defaultPictureRef::ﬁleName ; " " ; " " ) ) ]
[ No dialog ]
Exit Script [ ]
Else If [ defaultPictureRef::URL ≠ "" ]
Open URL [ Substitute ( defaultPictureRef::URL ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
End If
Else If [ defaultPictureTL::Picture ≠ ""
or defaultPictureTL::kﬁleLocation ≠ ""
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
Pause/Resume Script [ Indeﬁnitely ]
Perform Find [ ]
#
Set Variable [ $$stoploadCitation ]
Exit Script [ ]
Else If [ FilterValues ( defaultPictureTL::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & defaultPictureTL::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & defaultPictureTL::ﬁlename ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( defaultPictureTL::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
January 7, 平成26 17:17:04 Imagination Quality Management.fp7 - showCitationPicture1inNewWindow -3-pictures: showCitationPicture1inNewWindow
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & defaultPictureTL::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & defaultPictureTL::ﬁlename ; " " ; " " ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( defaultPictureTL::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagDefaultFolderPathTL::tag ; " " ; "%20" ) &
Case ( Left ( defaultPictureTL::ﬁlename ; 1 ) = "/" ; Substitute ( defaultPictureTL::ﬁlename ; " " ; "%20" ) ;
 "/" & Substitute ( defaultPictureTL::ﬁlename ; " " ; "%20" ) ) ]
[ No dialog ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagDefaultFolderPathTL::tag ; " " ; " " ) &
Case ( Left ( defaultPictureTL::ﬁlename ; 1 ) = "/" ; Substitute ( defaultPictureTL::ﬁlename ; " " ; " " ) ;
 "/" & Substitute ( defaultPictureTL::ﬁlename ; " " ; " " ) ) ]
[ No dialog ]
Exit Script [ ]
Else If [ defaultPictureTL::URL ≠ "" ]
Open URL [ Substitute ( defaultPictureTL::URL ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
End If
End If
#
#If there is no ﬁle found then ask user what picture
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
Close Window [ Name: "Discovery Picture"; Current ﬁle ]
New Window [ Name: "Discovery Picture"; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get (ScreenWidth)/4 ]
Go to Layout [ “reportPictureWindow” (testlearnReportTags) ]
Go to Field [ testlearnReportTags::Picture ]
Show Custom Dialog [ Message: "Select a picture to insert. "; Buttons: “OK” ]
Insert Picture [ ]
Go to Field [ ]
Go to Field [ ]
End If
January 7, 平成26 17:17:04 Imagination Quality Management.fp7 - showCitationPicture1inNewWindow -4-
