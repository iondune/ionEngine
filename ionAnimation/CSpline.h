
#pragma once

#include <ionCore.h>

#include "ISpline.h"
#include "ISplineInterpolator.h"
#include "CLinearSplineInterpolator.h"


namespace ion
{
	namespace Animation
	{

		int IntermediateToIndex(float const Mu);

		template <typename TSplineNode>
		class CSpline : public ISpline<TSplineNode>
		{

		protected:

			std::vector<TSplineNode> Nodes;
			std::vector<float> DistanceTable;
			float MuIncrement = 0;
			bool Looping = true;

			mutable SharedPointer<ISplineInterpolator<TSplineNode>> DefaultInterpolator = SharedFromNew(new CLinearSplineInterpolator<TSplineNode>());

		public:

			std::vector<TSplineNode> const & GetNodes() const;
			std::vector<TSplineNode> & GetNodes();

			void AddNode(TSplineNode const & Node);

			void SetLooping(bool const looping);
			bool IsLooping() const;

			void SetDefaultInterpolator(SharedPointer<ISplineInterpolator<TSplineNode>> defaultInterpolator);
			SharedPointer<ISplineInterpolator<TSplineNode>> GetDefaultInterpolator() const;

			int SanitizeIndex(int Index) const;

			TSplineNode const & GetNode(int const Index) const;
			TSplineNode GetNodeInterpolated(float const Intermediate, SharedPointer<ISplineInterpolator<TSplineNode>> Interpolator = 0) const;

			float BuildDistanceTable(float const Increment = 0.1f, SharedPointer<ISplineInterpolator<TSplineNode>> Interpolator = 0);
			float GetIntermediateFromDistance(float const Distance, SharedPointer<ISplineInterpolator<TSplineNode>> Interpolator = 0);
			TSplineNode GetNodeFromDistance(float const Distance, SharedPointer<ISplineInterpolator<TSplineNode>> Interpolator = 0);
			float GetTotalPathLength();

		};

		template <typename TSplineNode>
		std::vector<TSplineNode> const & CSpline<TSplineNode>::GetNodes() const
		{
			return Nodes;
		}

		template <typename TSplineNode>
		std::vector<TSplineNode> & CSpline<TSplineNode>::GetNodes()
		{
			return Nodes;
		}

		template <typename TSplineNode>
		void CSpline<TSplineNode>::AddNode(TSplineNode const & Node)
		{
			Nodes.push_back(Node);
			DistanceTable.clear();
		}

		template <typename TSplineNode>
		void CSpline<TSplineNode>::SetLooping(bool const looping)
		{
			DistanceTable.clear();
			Looping = looping;
		}

		template <typename TSplineNode>
		bool CSpline<TSplineNode>::IsLooping() const
		{
			return Looping;
		}

		template <typename TSplineNode>
		void CSpline<TSplineNode>::SetDefaultInterpolator(SharedPointer<ISplineInterpolator<TSplineNode>> defaultInterpolator)
		{
			DefaultInterpolator = defaultInterpolator;
		}

		template <typename TSplineNode>
		SharedPointer<ISplineInterpolator<TSplineNode>> CSpline<TSplineNode>::GetDefaultInterpolator() const
		{
			return DefaultInterpolator;
		}

		template <typename TSplineNode>
		int CSpline<TSplineNode>::SanitizeIndex(int Index) const
		{
			if (! Nodes.size())
				return -1;

			if (Looping)
			{
				while (Index < 0)
					Index += (int) Nodes.size();

				if (Index >= static_cast<int>(Nodes.size()))
					Index %= (int) Nodes.size();
			}
			else
			{
				Index = Clamp<int>(Index, 0, (int) Nodes.size() - 1);
			}

			return Index;
		}

		template <typename TSplineNode>
		TSplineNode const & CSpline<TSplineNode>::GetNode(int const Index) const
		{
			return Nodes[SanitizeIndex(Index)];
		}

		template <typename TSplineNode>
		TSplineNode CSpline<TSplineNode>::GetNodeInterpolated(float const Mu, SharedPointer<ISplineInterpolator<TSplineNode>> Interpolator) const
		{
			if (! Interpolator)
				Interpolator = DefaultInterpolator;

			if (! Interpolator)
				return TSplineNode();

			int const Index = SanitizeIndex(IntermediateToIndex(Mu));

			if (Index < 0)
				return TSplineNode();

			return Interpolator->Interpolate(* this, Index, fmodf(Mu, 1.f));
		}

		template <typename TSplineNode>
		float CSpline<TSplineNode>::BuildDistanceTable(float const Increment, SharedPointer<ISplineInterpolator<TSplineNode>> Interpolator)
		{
			if (! Interpolator)
				Interpolator = DefaultInterpolator;

			if (! Interpolator)
				return 0.f;

			if (! Nodes.size())
				return 0.f;

			DistanceTable.clear();
			// Store the increment at which this table was built
			MuIncrement = Increment;

			float const Max = static_cast<float>(Looping ? Nodes.size() : Nodes.size() - 1);
			TSplineNode Last = Interpolator->Interpolate(* this, 0, 0.f);
			DistanceTable.push_back(0.f);

			for (float Mu = Increment;; Mu += Increment)
			{
				if (Mu > Max)
				{
					TSplineNode Current = Interpolator->Interpolate(* this, SanitizeIndex(IntermediateToIndex(Max)), fmodf(Max, 1.f));
					DistanceTable.push_back((Current - Last).GetLength() + (DistanceTable.size() ? DistanceTable.back() : 0.f));
					break;
				}

				TSplineNode Current = Interpolator->Interpolate(* this, SanitizeIndex(IntermediateToIndex(Mu)), fmodf(Mu, 1.f));
				DistanceTable.push_back((Current - Last).GetLength() + (DistanceTable.size() ? DistanceTable.back() : 0.f));
				Last = Current;
			}

			return DistanceTable.back();
		}


		template <typename TSplineNode>
		float CSpline<TSplineNode>::GetIntermediateFromDistance(float const Distance, SharedPointer<ISplineInterpolator<TSplineNode>> Interpolator)
		{
			if (DistanceTable.size() == 0)
				BuildDistanceTable(0.1f, Interpolator);

			if (DistanceTable.size() == 0)
				return 0.f;

			uint Max = (uint) DistanceTable.size() - 1, Min = 0;

			float const ModulatedDistance = fmodf(Distance, DistanceTable.back());

			while (Max > Min + 1)
			{
				uint const Midpoint = (Max + Min) / 2;
				float const Value = DistanceTable[Midpoint];
				if (ModulatedDistance > Value)
					Min = Midpoint;
				else
					Max = Midpoint;
			}

			if (Max != Min + 1)
				std::cerr << "Unexpected values of Max and Min in getNodeArcLengthParametized(...): " << Min << " " << Max << std::endl;

			return (Min + (ModulatedDistance - DistanceTable[Min]) / (DistanceTable[Min+1] - DistanceTable[Min])) * MuIncrement;
		}

		template <typename TSplineNode>
		TSplineNode CSpline<TSplineNode>::GetNodeFromDistance(float const Distance, SharedPointer<ISplineInterpolator<TSplineNode>> Interpolator)
		{
			if (! Interpolator)
				Interpolator = DefaultInterpolator;

			if (! Interpolator)
				return TSplineNode();

			float const Mu = GetIntermediateFromDistance(Distance);
			int const Index = SanitizeIndex(IntermediateToIndex(Mu));

			if (Index < 0)
				return TSplineNode();

			return Interpolator->Interpolate(* this, Index, fmodf(Mu, 1.f));
		}

		template <typename TSplineNode>
		float CSpline<TSplineNode>::GetTotalPathLength()
		{
			if (DistanceTable.size() == 0)
			{
				BuildDistanceTable(0.1f);
			}

			if (DistanceTable.size() == 0)
			{
				return 0.f;
			}

			return DistanceTable.back();
		}

	}
}
