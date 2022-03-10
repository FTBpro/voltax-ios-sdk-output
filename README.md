# Voltax SDK for iOS

This library provides an easy integration with Voltax player into a native iOS app.

## Implementation

### Add the SDK to your project

#### [CocoaPods](https://cocoapods.org/)

* Set dependency as follows: `pod 'VoltaxSDK'`
* Execute `pod install` in Terminal.
* Open workspace file and run.

### Create a container view to hold the MMVideoView

The `MMVideoView` should be loaded into a container view (UIView). This container view can be the `contentView` of a `UICollectionView` or `UITableView` `cell`.

### Initialize a MMVideoView instance

The `MMVideoView`is being initialized with the following properties:

1. `playerId` - The Player ID.
2. `contentId` - The Content ID of the Player.
3. `articleUrl` (optional) - The URL of the article page.

Initialize a new instance of `MMVideoView` using one of the following constructors:

```Swift
let mmVideoView = MMVideoView(playerId: PLAYER_ID, contentId: CONTENT_ID)
```

```Swift
let mmVideoView = MMVideoView(playerId: PLAYER_ID, contentId: CONTENT_ID, articleUrl: ARTICLE_URL)
```

### MMVideoViewDelegate

You have to impelement `MMVideoViewDelegate` and set it to the instance of the `MMVideoView`.
The `MMVideoViewDelegate` has one methods:

`mmVideoViewHeight(_ height: CGFloat)` - See "MMVideoView Height Changes" section below.

Set the delegate to `MMVideoView` instance:

```Swift
mmVideoView.delegate = self
```

### Load the Voltax player to the MMVideoView

In order to load the player to your `MMVideoView` instance, use the `load()` method.

```Swift
@IBOutlet weak var mmVideoViewContainer: UIView!

mmVideoView.load(mmVideoViewContainer)
```

Or for UICollectionView or UITableView, in `willDisplay cell` method:

```Swift
mmVideoView.load(cell.contentView)
```

### MMVideoView Height Changes

#### Custom View

1. Hold an outlet to your container view height.
2. Implement `mmVideoViewHeight(_ height: CGFloat)` method of `MMVideoViewDelegate` - update the container view height using the outlet.
3. If your app supports orientation changes - in `viewWillTransition` method, call to `mmVideoView.viewWillTransition(coordinator)`

#### UICollectionView item

1. Hold a variable for the `MMVideoView` view height and initialize it to 0.
```Swift
var mmVideoViewCellHeight: CGFloat = 0
```
2. Implement `mmVideoViewHeight(_ height: CGFloat)` method of `MMVideoViewDelegate` as follows:
```Swift
func mmVideoViewHeight(_ height: CGFloat) {
    self.mmVideoViewCellHeight = height
    self.collectionView.performBatchUpdates(nil, completion: nil)
}
```
3. In `sizeForItemAt` method of UICollectionViewDelegateFlowLayout, set player item height to:
```Swift
CGSize(width: width, height: mmVideoViewCellHeight)
```
4. In `willDisplay cell` method, call to `self.mmVideoView.willDisplay()` for the `MMVideoView` item `indexPath`.
5. If your app supports orientation changes - in `viewWillTransition` method, call to `mmVideoView.viewWillTransition(coordinator)` and invalidate the collectionView layout. For example:
```Swift
override func viewWillTransition(to size: CGSize, with coordinator: UIViewControllerTransitionCoordinator) {
    super.viewWillTransition(to: size, with: coordinator)
    collectionView.collectionViewLayout.invalidateLayout()
    mmVideoView.viewWillTransition(coordinator)
}
```

#### UITableView item

1. Hold a variable for the `MMVideoView` view height and initialize it to 0.
```Swift
var mmVideoViewCellHeight: CGFloat = 0
```
2. Implement `mmVideoViewHeight(_ height: CGFloat)` method of `MMVideoViewDelegate` as follows:
```Swift
func mmVideoViewHeight(_ height: CGFloat) {
    self.mmVideoViewCellHeight = height
    self.tableView.beginUpdates()
    self.tableView.endUpdates()
}
```
3. In `heightForRowAt` method of `UITableViewDelegate`, set player item height to `self.mmVideoViewCellHeight`.
4. In `willDisplay cell` method, call to `self.mmVideoView.willDisplay()` for the `MMVideoView` item `indexPath`.
5. If your app supports orientation changes - in `viewWillTransition` method, call to `mmVideoView.viewWillTransition(coordinator)`:
```Swift
override func viewWillTransition(to size: CGSize, with coordinator: UIViewControllerTransitionCoordinator) {
    super.viewWillTransition(to: size, with: coordinator)

    mmVideoView.viewWillTransition(coordinator)
}
```

### Additional `MMVideoView` methods

- `play()` - use this method to play the player.
- `pause()` - use this method to pause the player.

### (Optional) Handle click on url

By default, click on url will open a `SFSafariViewController`.
If you want to change this, you can implement the `MMVideoViewDelegate` method: `func click(on url: URL)` and handle click on url by yourself.
Don't forget to set the delegate of your `MMVideoView` instance.

### (Optional) On player load callback

To know when the player is loaded, you can implement the `MMVideoViewDelegate` method: `func onPlayerLoaded()`.
Don't forget to set the delegate of your `MMVideoView` instance.

### (Optional) On player Error callback

To recieve error events of the player, you can implement the `MMVideoViewDelegate` method: `func onPlayerError(_ error: MMVideoViewError)`.
Don't forget to set the delegate of your `MMVideoView` instance.
```swift
func onPlayerError(_ error: MMVideoViewError) {
    let message: String = error.message as String
    let code: Int = error.code.intValue
    let isFatalError = error.isFatalError
    // Do something
}
```

## Monetization

### Step 1 - Add Google ads IMA dependency

In Podfile, add GoogleAds-IMA-iOS-SDK:
```swift
pod 'GoogleAds-IMA-iOS-SDK', '~> 3.14'
```

### Step 2 - Add the MMIMAAdsHandler file to your project

Copy the following file and place it in your project:
```swift
//
//  MMIMAAdsHandler.swift
//  VoltaxDemo
//
//  Created by Alon Shprung on 16/01/2022.
//

import Foundation
import GoogleInteractiveMediaAds
import VoltaxSDK
import UIKit

class MMIMAAdsHandler: NSObject, MMIMAAdsProvider {
    var delegate: MMIMAAdsProviderDelegate?
    
    weak var vc: UIViewController? = nil
    
    private var adsLoader: IMAAdsLoader!
    private var adsManager: IMAAdsManager!
    
    private var adDisplayContainer: UIView?
    
    private var soundOnOffView: UIView?
    
    init(vc: UIViewController) {
        self.vc = vc
        super.init()
        
        self.setUpAdsLoader()
    }
    
    func setUpAdsLoader() {
      adsLoader = IMAAdsLoader(settings: nil)
      adsLoader.delegate = self
    }
    
    func requestAds(in view: UIView, with tagUrl: String) {
        // Create ad display container for ad rendering.
        let adDisplayContainer = IMAAdDisplayContainer(
          adContainer: view, viewController: vc, companionSlots: nil)
        self.adDisplayContainer = view
        // Create an ad request with our ad tag, display container, and optional user context.
        let request = IMAAdsRequest(
          adTagUrl: tagUrl,
          adDisplayContainer: adDisplayContainer,
          contentPlayhead: nil,
          userContext: nil)

        adsLoader.requestAds(with: request)
    }
    
    func isPlaying() -> Bool {
        return adsManager?.adPlaybackInfo.isPlaying ?? false
    }
    
    func isMuted() -> Bool {
        return adsManager?.volume == 0
    }
    
    func requestAdsManager(to task: MMIMAAdsManagerTask) {
        guard let adsManager = self.adsManager else { return }
        switch task {
        case .ADS_MANAGER_START:
            adsManager.start()
            break
        case .ADS_MANAGER_PAUSE:
            adsManager.pause()
            break
        case .ADS_MANAGER_RESUME:
            adsManager.resume()
            break
        case .ADS_MANAGER_MUTE:
            adsManager.volume = 0
            break
        case .ADS_MANAGER_UNMUTE:
            adsManager.volume = 1
            break
        @unknown default:
            break
        }
    }
    
    private func addSoundOnOffView() {
        if (self.soundOnOffView == nil) {
            let view = UIView()
            
            self.vc?.view.addSubview(view)
            
            delegate?.handleSound(view)
            
            self.soundOnOffView = view
            
            view.translatesAutoresizingMaskIntoConstraints = false
            self.vc?.view.addConstraints([
                view.topAnchor.constraint(equalTo: self.adDisplayContainer!.topAnchor),
                view.leadingAnchor.constraint(equalTo: self.adDisplayContainer!.leadingAnchor),
                view.widthAnchor.constraint(equalToConstant: 44.0),
                view.heightAnchor.constraint(equalToConstant: 44.0)
            ])
        }
    }
}

// MARK: - IMAAdsLoaderDelegate

extension MMIMAAdsHandler: IMAAdsLoaderDelegate {
    func adsLoader(_ loader: IMAAdsLoader, adsLoadedWith adsLoadedData: IMAAdsLoadedData) {
        // Grab the instance of the IMAAdsManager and set ourselves as the delegate.
        adsManager = adsLoadedData.adsManager
        adsManager.delegate = self

        // Create ads rendering settings and tell the SDK to use the in-app browser.
        let adsRenderingSettings = IMAAdsRenderingSettings()
        adsRenderingSettings.linkOpenerPresentingController = vc

        // Initialize the ads manager.
        adsManager.initialize(with: adsRenderingSettings)
    }
    
    func adsLoader(_ loader: IMAAdsLoader, failedWith adErrorData: IMAAdLoadingErrorData) {
        delegate?.adsLoaderDidRecieveError(adErrorData.adError.message)
    }
}

// MARK: - IMAAdsManagerDelegate

extension MMIMAAdsHandler: IMAAdsManagerDelegate {
    func adsManager(_ adsManager: IMAAdsManager, didReceive event: IMAAdEvent) {
        var mmAdEvent: MMIMAAdEvent? = nil
        guard let ad = event.ad else { return }
        
        switch event.type {
        case .LOADED:
            mmAdEvent = .EVENT_LOADED
            break
        case .PAUSE:
            mmAdEvent = .EVENT_PAUSE
            break
        case .RESUME:
            mmAdEvent = .EVENT_RESUME
            break
        case .TAPPED:
            mmAdEvent = .EVENT_TAPPED
            break
        case .CLICKED:
            mmAdEvent = .EVENT_CLICKED
            break
        case .COMPLETE:
            mmAdEvent = .EVENT_COMPLETE
            break
        case .STARTED:
            mmAdEvent = .EVENT_STARTED
            if (ad.contentType != "application/javascript") {
                self.addSoundOnOffView()
            }
            break
        case .SKIPPED:
            mmAdEvent = .EVENT_SKIPPED
            break
        case .FIRST_QUARTILE:
            mmAdEvent = .EVENT_FIRST_QUARTILE
            break
        case .THIRD_QUARTILE:
            mmAdEvent = .EVENT_THIRD_QUARTILE
            break
        case .MIDPOINT:
            mmAdEvent = .EVENT_MIDPOINT
            break
        default:
            break
        }
        if let mmAdEvent = mmAdEvent {
            let adObject = MMIMAAd(currentPosition: adsManager.adPlaybackInfo.currentMediaTime, duration: ad.duration, adPosition: Int32(ad.adPodInfo.adPosition), contentType: ad.contentType)
            
            delegate?.adsManagerDidRecieveEvent(mmAdEvent, ad: adObject)
        }
    }
    
    func adsManager(_ adsManager: IMAAdsManager, didReceive error: IMAAdError) {
        delegate?.adsManagerDidRecieveError(error.message)
    }
    
    func adsManagerDidRequestContentPause(_ adsManager: IMAAdsManager) {
        delegate?.adsManagerDidRequestContentPause()
    }
    
    func adsManagerDidRequestContentResume(_ adsManager: IMAAdsManager) {
        delegate?.adsManagerDidRequestContentResume()
        self.soundOnOffView?.removeFromSuperview()
        self.soundOnOffView = nil
    }
}
```

### Step 3 - MMIMAAdsProvider instance in your UIViewController

Initialize a MMIMAAdsProvider instance in the UIViewController that showing the MMVideoView.
```swift
mmImaAdsHandler = MMIMAAdsHandler(vc: self)
```

### Step 4 - set the adsProvider for the MMVideoView instance

```swift
mmVideoView.adsProvider = mmImaAdsHandler
```
