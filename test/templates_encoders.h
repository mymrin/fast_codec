#include "templates.h"

void Encode(fast_codec::Encoder& encoder, const DefaultIncrementalRefreshMessage& msg);
void Encode(fast_codec::Encoder& encoder, const DefaultSnapshotMessage& msg);
void Encode(fast_codec::Encoder& encoder, const SecurityDefinition& msg);
void Encode(fast_codec::Encoder& encoder, const SecurityDefinitionUpdateReport& msg);
void Encode(fast_codec::Encoder& encoder, const SecurityStatus& msg);
void Encode(fast_codec::Encoder& encoder, const Heartbeat& msg);
void Encode(fast_codec::Encoder& encoder, const SequenceReset& msg);
void Encode(fast_codec::Encoder& encoder, const TradingSessionStatus& msg);
void Encode(fast_codec::Encoder& encoder, const News& msg);
void Encode(fast_codec::Encoder& encoder, const Logon& msg);
void Encode(fast_codec::Encoder& encoder, const Logout& msg);
