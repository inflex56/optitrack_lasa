#pragma once

#include <string>
#include <memory>
#include <functional>

#include <NatNet/NatNetClient.h>
#include <NatNet/NatNetTypes.h>

namespace optitrack {

typedef std::function<void(sFrameOfMocapData* data)> DataHandlerCallback;

class OptiTrackClient {
public:
  OptiTrackClient();
  ~OptiTrackClient();

  int connect(const std::string& serverIP);
  void disconnect();

  bool testConnection();
  bool requestDataDescription();

  void setCallback(const DataHandlerCallback& callback);
  void evaluateCallback(sFrameOfMocapData* data);

  static void NATNET_CALLCONV dataHandler(sFrameOfMocapData* data, void* context);

private:
  std::unique_ptr<NatNetClient> client_ = nullptr;
  sNatNetClientConnectParams clientConnectParams_;
  sServerDescription serverDescription_;

  DataHandlerCallback callback_ = nullptr;
};

}

