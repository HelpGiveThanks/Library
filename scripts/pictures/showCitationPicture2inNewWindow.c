pictures: showCitationPicture2inNewWindow
#
#Determine where reference picture or movie is located
#on the tag menus window and then open it.
If [ citationPicture2::picture ≠ ""
or citationPicture2::kfileLocation ≠ ""
or citationPicture2::URL ≠ "" ]
If [ citationPicture2::picture ≠ "" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $picture; Value:tagMenus::Kpicture2 ]
Go to Field [ ]
#
New Window [ Name: citationPicture2::picture; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get (ScreenWidth)/4 ]
Go to Layout [ “ReferencePictureWindow” (reference) ]
#
Enter Find Mode [ ]
Set Field [ reference::_Lreference; $picture ]
Perform Find [ ]
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
Else If [ FilterValues ( citationPicture2::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citationPicture2::fileName ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citationPicture2::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & citationPicture2::fileName ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citationPicture2::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagPathPicture2_button::tag ; " " ; "%20" ) &
Case ( Left ( citationPicture2::fileName ; 1 ) = "/" ; Substitute ( citationPicture2::fileName ; " " ; "%20" ) ;
 "/" & Substitute ( citationPicture2::fileName ; " " ; "%20" ) ) ]
[ No dialog ]
Exit Script [ ]
Else If [ citationPicture2::URL ≠ "" ]
Open URL [ Substitute ( citationPicture2::URL ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
End If
End If
#
#Determine where testlearn picture or movie is located
#on the tag menus window and then open it.
If [ TLPicture2::Picture ≠ ""
or TLPicture2::kfileLocation ≠ ""
or TLPicture2::URL ≠ "" ]
If [ TLPicture2::Picture ≠ "" ]
#To speed up script, stop this script from working.
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $picture; Value:tagMenus::Kpicture2 ]
Go to Field [ ]
#
New Window [ Name: TLPicture2::Picture; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4; Left: Get (ScreenWidth)/4 ]
Go to Layout [ “LearnPictureWindow” (testlearn) ]
#
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $picture ]
Perform Find [ ]
#
Set Variable [ $$stoploadCitation ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
Else If [ FilterValues ( TLPicture2::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & TLPicture2::filename ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( TLPicture2::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & TLPicture2::filename ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( TLPicture2::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( tagTLPathPicture2_button::tag & TLPicture2::filename ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ TLPicture2::URL ≠ "" ]
Open URL [ Substitute ( TLPicture2::URL ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
End If
End If
#
January 7, 平成26 17:17:40 Imagination Quality Management.fp7 - showCitationPicture2inNewWindow -1-
