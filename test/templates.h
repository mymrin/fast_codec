#include <cstdint>
#include <string>
#include "codec/fast_codec.h"

struct DefaultIncrementalRefreshMessage
{
   static const std::uint32_t id = 1;

   // static const std::string ApplVerID = "9";
   // static const std::string MessageType = "X";
   // static const std::string SenderCompID = "MOEX";
   std::uint32_t MsgSeqNum;
   std::uint64_t SendingTime;
   fast_codec::uint32_nt LastFragment;

   struct MDEntries
   {
      std::uint32_t MDUpdateAction;
      std::string MDEntryType;
      fast_codec::uint64_nt SecurityID;
      static const std::uint32_t SecurityIDSource = 8;
      fast_codec::string_nt Symbol;
      fast_codec::string_nt SecurityGroup;
      fast_codec::uint32_nt ExchangeTradingSessionID;
      std::uint32_t RptSeq;
      fast_codec::uint32_nt MarketDepth;
      fast_codec::uint32_nt MDPriceLevel;
      fast_codec::int64_nt MDEntryID;
      fast_codec::DecimalNullable MDEntryPx;
      fast_codec::int64_nt MDEntrySize;
      fast_codec::uint32_nt MDEntryDate;
      std::uint32_t MDEntryTime;
      fast_codec::int32_nt NumberOfOrders;
      fast_codec::string_nt MDEntryTradeType;
      fast_codec::int32_nt TrdType;
      fast_codec::DecimalNullable LastPx;
      fast_codec::int32_nt MDFlags;
      fast_codec::string_nt Currency;
      fast_codec::uint64_nt Revision;
      fast_codec::string_nt OrderSide;
   };
   std::vector<MDEntries> MDEntriesSeq;
};

struct DefaultSnapshotMessage
{
   static const std::uint32_t id = 2;

   // static const std::string ApplVerID = "9";
   // static const std::string MessageType = "W";
   // static const std::string SenderCompID = "MOEX";
   std::uint32_t MsgSeqNum;
   std::uint64_t SendingTime;
   fast_codec::uint32_nt LastFragment;
   std::uint32_t RptSeq;
   std::uint32_t TotNumReports;
   std::uint32_t LastMsgSeqNumProcessed;
   fast_codec::uint64_nt SecurityID;
   static const std::uint32_t SecurityIDSource = 8;
   fast_codec::string_nt Symbol;
   fast_codec::string_nt SecurityGroup;

   struct MDEntries
   {
      std::string MDEntryType;
      fast_codec::uint32_nt ExchangeTradingSessionID;
      fast_codec::int64_nt MDEntryID;
      fast_codec::uint32_nt MarketDepth;
      fast_codec::DecimalNullable MDEntryPx;
      fast_codec::uint32_nt MDEntryDate;
      std::uint32_t MDEntryTime;
      fast_codec::int64_nt MDEntrySize;
      fast_codec::uint32_nt MDPriceLevel;
      fast_codec::int32_nt NumberOfOrders;
      fast_codec::string_nt MDEntryTradeType;
      fast_codec::int32_nt TrdType;
      fast_codec::int32_nt MDFlags;
      fast_codec::string_nt Currency;
      fast_codec::string_nt OrderSide;
   };
   std::vector<MDEntries> MDEntriesSeq;
};

struct SecurityDefinition
{
   static const std::uint32_t id = 3;

   // static const std::string ApplVerID = "9";
   // static const std::string MessageType = "d";
   // static const std::string SenderCompID = "MOEX";
   std::uint32_t MsgSeqNum;
   std::uint64_t SendingTime;
   std::uint32_t TotNumReports;
   std::string Symbol;
   fast_codec::string_nt SecurityDesc;
   std::uint64_t SecurityID;
   static const std::uint32_t SecurityIDSource = 8;
   fast_codec::string_nt SecurityAltID;
   fast_codec::string_nt SecurityAltIDSource;
   fast_codec::string_nt SecurityType;
   fast_codec::string_nt CFICode;
   fast_codec::DecimalNullable StrikePrice;
   fast_codec::DecimalNullable ContractMultiplier;
   fast_codec::uint32_nt SecurityTradingStatus;
   fast_codec::string_nt Currency;
   // static const std::string MarketID = "MOEX";
   std::string MarketSegmentID;
   fast_codec::uint32_nt TradingSessionID;
   fast_codec::uint32_nt ExchangeTradingSessionID;
   fast_codec::DecimalNullable Volatility;

   struct MDFeedTypes
   {
      std::string MDFeedType;
      fast_codec::uint32_nt MarketDepth;
      fast_codec::uint32_nt MDBookType;
   };
   std::vector<MDFeedTypes> MDFeedTypesSeq;

   struct Underlyings
   {
      std::string UnderlyingSymbol;
      fast_codec::uint64_nt UnderlyingSecurityID;
   };
   std::vector<Underlyings> UnderlyingsSeq;
   fast_codec::DecimalNullable HighLimitPx;
   fast_codec::DecimalNullable LowLimitPx;
   fast_codec::DecimalNullable MinPriceIncrement;
   fast_codec::DecimalNullable MinPriceIncrementAmount;
   fast_codec::DecimalNullable InitialMarginOnBuy;
   fast_codec::DecimalNullable InitialMarginOnSell;
   fast_codec::DecimalNullable InitialMarginSyntetic;
   fast_codec::string_nt QuotationList;
   fast_codec::DecimalNullable TheorPrice;
   fast_codec::DecimalNullable TheorPriceLimit;

   struct InstrumentLegs
   {
      std::string LegSymbol;
      std::uint64_t LegSecurityID;
      fast_codec::Decimal LegRatioQty;
   };
   std::vector<InstrumentLegs> InstrumentLegsSeq;

   struct InstrumentAttributes
   {
      std::int32_t InstrAttribType;
      std::string InstrAttribValue;
   };
   std::vector<InstrumentAttributes> InstrumentAttributesSeq;
   fast_codec::DecimalNullable UnderlyingQty;
   fast_codec::string_nt UnderlyingCurrency;

   struct EvntGrp
   {
      std::int32_t EventType;
      std::uint32_t EventDate;
      std::uint64_t EventTime;
   };
   std::vector<EvntGrp> EvntGrpSeq;
   fast_codec::uint32_nt MaturityDate;
   fast_codec::uint32_nt MaturityTime;
};

struct SecurityDefinitionUpdateReport
{
   static const std::uint32_t id = 4;

   // static const std::string ApplVerID = "9";
   // static const std::string MessageType = "BP";
   // static const std::string SenderCompID = "MOEX";
   std::uint32_t MsgSeqNum;
   std::uint64_t SendingTime;
   std::uint64_t SecurityID;
   static const std::uint32_t SecurityIDSource = 8;
   fast_codec::DecimalNullable Volatility;
   fast_codec::DecimalNullable TheorPrice;
   fast_codec::DecimalNullable TheorPriceLimit;
};

struct SecurityStatus
{
   static const std::uint32_t id = 5;

   // static const std::string ApplVerID = "9";
   // static const std::string MessageType = "f";
   // static const std::string SenderCompID = "MOEX";
   std::uint32_t MsgSeqNum;
   std::uint64_t SendingTime;
   std::uint64_t SecurityID;
   static const std::uint32_t SecurityIDSource = 8;
   std::string Symbol;
   fast_codec::uint32_nt SecurityTradingStatus;
   fast_codec::DecimalNullable HighLimitPx;
   fast_codec::DecimalNullable LowLimitPx;
   fast_codec::DecimalNullable InitialMarginOnBuy;
   fast_codec::DecimalNullable InitialMarginOnSell;
   fast_codec::DecimalNullable InitialMarginSyntetic;
};

struct Heartbeat
{
   static const std::uint32_t id = 6;

   // static const std::string ApplVerID = "9";
   // static const std::string MessageType = "0";
   // static const std::string SenderCompID = "MOEX";
   std::uint32_t MsgSeqNum;
   std::uint64_t SendingTime;
};

struct SequenceReset
{
   static const std::uint32_t id = 7;

   // static const std::string ApplVerID = "9";
   // static const std::string MessageType = "4";
   // static const std::string SenderCompID = "MOEX";
   std::uint32_t MsgSeqNum;
   std::uint64_t SendingTime;
   std::uint32_t NewSeqNo;
};

struct TradingSessionStatus
{
   static const std::uint32_t id = 8;

   // static const std::string ApplVerID = "9";
   // static const std::string MessageType = "h";
   // static const std::string SenderCompID = "MOEX";
   std::uint32_t MsgSeqNum;
   std::uint64_t SendingTime;
   std::uint64_t TradSesOpenTime;
   std::uint64_t TradSesCloseTime;
   fast_codec::uint64_nt TradSesIntermClearingStartTime;
   fast_codec::uint64_nt TradSesIntermClearingEndTime;
   std::uint32_t TradingSessionID;
   fast_codec::uint32_nt ExchangeTradingSessionID;
   std::uint32_t TradSesStatus;
   // static const std::string MarketID = "MOEX";
   std::string MarketSegmentID;
   fast_codec::int32_nt TradSesEvent;
};

struct News
{
   static const std::uint32_t id = 9;

   // static const std::string ApplVerID = "9";
   // static const std::string MessageType = "B";
   // static const std::string SenderCompID = "MOEX";
   std::uint32_t MsgSeqNum;
   std::uint64_t SendingTime;
   fast_codec::uint32_nt LastFragment;
   fast_codec::string_nt NewsId;
   fast_codec::uint64_nt OrigTime;
   fast_codec::string_nt LanguageCode;
   fast_codec::uint32_nt Urgency;
   std::string Headline;
   // static const std::string MarketID = "MOEX";
   fast_codec::string_nt MarketSegmentID;

   struct NewsText
   {
      std::string Text;
   };
   std::vector<NewsText> NewsTextSeq;
};

struct Logon
{
   static const std::uint32_t id = 1000;

   // static const std::string ApplVerID = "9";
   // static const std::string MessageType = "A";
   // static const std::string SenderCompID = "MOEX";
   std::uint32_t MsgSeqNum;
   std::uint64_t SendingTime;
};

struct Logout
{
   static const std::uint32_t id = 1001;

   // static const std::string ApplVerID = "9";
   // static const std::string MessageType = "5";
   // static const std::string SenderCompID = "MOEX";
   std::uint32_t MsgSeqNum;
   std::uint64_t SendingTime;
   fast_codec::string_nt Text;
};

