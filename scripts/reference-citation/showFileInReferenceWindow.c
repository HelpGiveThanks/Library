reference(citation): showFileInReferenceWindow
#
#Show reference file.
If [ FilterValues ( citationTitle1::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute (Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citationTitle1::fileName ; " " ; "%20" ) ]
[ No dialog ]
Else If [ FilterValues ( citationTitle1::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & citationTitle1::fileName ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citationTitle1::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
If [ Right (citationTitle1::fileName ; 3) = "mp4"
 or Right (citationTitle1::fileName ; 3) = "mov" ]
Open URL [ Substitute ( tagFolderPathForFile::tag & citationTitle1::fileName ; " " ; "%20" ) ]
[ No dialog ]
Else
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagFolderPathForFile::tag ; " " ; "%20" ) &
Case ( Left ( citationTitle1::fileName ; 1 ) = "/" ; Substitute ( citationTitle1::fileName ; " " ; "%20" ) ;
 "/" & Substitute ( citationTitle1::fileName ; " " ; "%20" ) ) ]
[ No dialog ]
End If
Else If [ citationTitle1::URL ≠ "" ]
Open URL [ citationTitle1::URL ]
[ No dialog ]
End If
#
#Show testlearn file.
If [ FilterValues ( TLTitle1::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & TLTitle1::filename ; " " ; "%20" ) ]
[ No dialog ]
Else If [ FilterValues ( TLTitle1::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & TLTitle1::filename ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( TLTitle1::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( tagTLFolderPathForFile1::tag & TLTitle1::filename ; " " ; "%20" ) ]
[ No dialog ]
Else If [ TLTitle1::URL ≠ "" ]
Open URL [ TLTitle1::URL ]
[ No dialog ]
End If
#
#Show path folder.
If [ tagMenus::tag ≠ "" and $$citationMatch = "path" ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagMenus::tag ; " " ; "%20" ) ]
[ No dialog ]
End If
January 7, 平成26 17:36:58 Imagination Quality Management.fp7 - showFileInReferenceWindow -1-
