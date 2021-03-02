# Voltax SDK for iOS

This library provides an easy integration with Voltax player into a native iOS app.

## Implementation

### Add the SDK to your project

#### [CocoaPods](https://cocoapods.org/)

* Set dependency as follows: `pod 'VoltaxSDK'`
* Execute `pod install` in Terminal.
* Open workspace file and run.

### The MMVideoView Class

`MMVideoView` is the main class of the Voltax SDK.

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
