#
#  Be sure to run `pod spec lint VoltaxSDK.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
#  To learn more about Podspec attributes see http://docs.cocoapods.org/specification.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
#

Pod::Spec.new do |s|

  # ―――  Spec Metadata  ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  These will help people to find your library, and whilst it
  #  can feel like a chore to fill in it's definitely to your advantage. The
  #  summary should be tweet-length, and the description more in depth.
  #

  s.name                = "VoltaxSDK"
  s.version             = "1.1.1"
  s.summary             = "VoltaxSDK iOS SDK for app developers"
  s.description         = "VoltaxSDK iOS SDK for app developers"
  s.homepage            = "https://www.minutemedia.com"
  s.license             = { :type => 'Proprietary', :text => 'Copyright 2021 Minute Media. All rights reserved.' }
  s.author              = { "Boris Kalim" => "boris@minutemedia.com" }
  s.platform            = :ios, "10.3"
  s.source              = { :git => "https://github.com/FTBpro/voltax-ios-sdk-output", :tag => s.version }
  s.requires_arc        = true
  s.preserve_paths      = "VoltaxSDK.xcframework"
  s.vendored_frameworks = "VoltaxSDK.xcframework"
  s.exclude_files       = ""

end
