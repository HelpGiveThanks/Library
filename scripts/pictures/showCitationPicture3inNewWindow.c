pictures: showCitationPicture3inNewWindow
#
#Determine where reference picture or movie is located
#on the tag menus window and then open it.
If [ citationPicture3::picture ≠ ""
or citationPicture3::kﬁleLocation ≠ ""
or citationPicture3::URL ≠ "" ]
If [ citationPicture3::picture ≠ "" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $picture; Value:tagMenus::Kpicture3 ]
Go to Field [ ]
#
New Window [ Name: citationPicture3::picture; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get (ScreenWidth)/4 ]
Go to Layout [ “ReferencePictureWindow” (reference) ]
#
Enter Find Mode [ ]
Set Field [ reference::_Lreference; $picture ]
Perform Find [ ]
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indeﬁnitely ]
Exit Script [ ]
Else If [ FilterValues ( citationPicture3::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citationPicture3::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citationPicture3::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & citationPicture3::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citationPicture3::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:/" ; "ﬁle:///" ) & tagPathPicture3_button::tag ; " " ; "%20" ) &
Case ( Left ( citationPicture3::ﬁleName ; 1 ) = "/" ; Substitute ( citationPicture3::ﬁleName ; " " ; "%20" ) ;
 "/" & Substitute ( citationPicture3::ﬁleName ; " " ; "%20" ) ) ]
[ No dialog ]
Exit Script [ ]
Else If [ citationPicture3::URL ≠ "" ]
Open URL [ Substitute ( citationPicture3::URL ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
End If
End If
#
#Determine where testlearn picture or movie is located
#on the tag menus window and then open it.
If [ TLPicture3::Picture ≠ ""
or TLPicture3::kﬁleLocation ≠ ""
or TLPicture3::URL ≠ "" ]
If [ TLPicture3::Picture ≠ "" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $picture; Value:tagMenus::Kpicture3 ]
Go to Field [ ]
#
New Window [ Name: TLPicture3::Picture; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get (ScreenWidth)/4 ]
Go to Layout [ “LearnPictureWindow” (testlearn) ]
#
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $picture ]
Perform Find [ ]
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indeﬁnitely ]
Exit Script [ ]
Else If [ FilterValues ( TLPicture3::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & TLPicture3::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( TLPicture3::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & TLPicture3::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( TLPicture3::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( tagTLPathPicture3_button::tag & TLPicture3::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ TLPicture3::URL ≠ "" ]
Open URL [ Substitute ( TLPicture3::URL ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
End If
End If
#
January 7, 平成26 17:18:13 Imagination Quality Management.fp7 - showCitationPicture3inNewWindow -1-
