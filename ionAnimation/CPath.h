
#pragma once

#include <ionCore.h>

#include "IPath.h"
#include "IInterpolator.h"
#include "CLinearInterpolator.h"


namespace ion
{
	namespace Animation
	{

		int IntermediateToIndex(float const Mu);

		template <typename TPathNode>
		class CPath : public IPath<TPathNode>
		{

		protected:

			std::vector<TPathNode> Nodes;
			std::vector<f32> DistanceTable;
			f32 MuIncrement = 0;
			bool Looping = true;

			mutable SharedPtr<IInterpolator<TPathNode>> DefaultInterpolator = SharedFromNew(new CLinearInterpolator<TPathNode>());

		public:

			std::vector<TPathNode> const & GetNodes() const;
			std::vector<TPathNode> & GetNodes();

			void AddNode(TPathNode const & Node);

			void SetLooping(bool const looping);
			bool IsLooping() const;

			void SetDefaultInterpolator(SharedPtr<IInterpolator<TPathNode>> defaultInterpolator);
			SharedPtr<IInterpolator<TPathNode>> GetDefaultInterpolator() const;

			int SanitizeIndex(int Index) const;

			TPathNode const & GetNode(int const Index) const;
			TPathNode GetNodeInterpolated(float const Intermediate, SharedPtr<IInterpolator<TPathNode>> Interpolator = 0) const;

			float BuildDistanceTable(float const Increment = 0.1f, SharedPtr<IInterpolator<TPathNode>> Interpolator = 0);
			float GetIntermediateFromDistance(float const Distance, SharedPtr<IInterpolator<TPathNode>> Interpolator = 0);
			TPathNode GetNodeFromDistance(float const Distance, SharedPtr<IInterpolator<TPathNode>> Interpolator = 0);
			float GetTotalPathLength();

		};

		template <typename TPathNode>
		std::vector<TPathNode> const & CPath<TPathNode>::GetNodes() const
		{
			return Nodes;
		}

		template <typename TPathNode>
		std::vector<TPathNode> & CPath<TPathNode>::GetNodes()
		{
			return Nodes;
		}

		template <typename TPathNode>
		void CPath<TPathNode>::AddNode(TPathNode const & Node)
		{
			Nodes.push_back(Node);
			DistanceTable.clear();
		}

		template <typename TPathNode>
		void CPath<TPathNode>::SetLooping(bool const looping)
		{
			DistanceTable.clear();
			Looping = looping;
		}

		template <typename TPathNode>
		bool CPath<TPathNode>::IsLooping() const
		{
			return Looping;
		}

		template <typename TPathNode>
		void CPath<TPathNode>::SetDefaultInterpolator(SharedPtr<IInterpolator<TPathNode>> defaultInterpolator)
		{
			DefaultInterpolator = defaultInterpolator;
		}

		template <typename TPathNode>
		SharedPtr<IInterpolator<TPathNode>> CPath<TPathNode>::GetDefaultInterpolator() const
		{
			return DefaultInterpolator;
		}

		template <typename TPathNode>
		int CPath<TPathNode>::SanitizeIndex(int Index) const
		{
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

		template <typename TPathNode>
		TPathNode const & CPath<TPathNode>::GetNode(int const Index) const
		{
			return Nodes[SanitizeIndex(Index)];
		}

		template <typename TPathNode>
		TPathNode CPath<TPathNode>::GetNodeInterpolated(float const Mu, SharedPtr<IInterpolator<TPathNode>> Interpolator) const
		{
			if (! Interpolator)
				Interpolator = DefaultInterpolator;

			if (! Interpolator)
				return TPathNode();

			int const Index = SanitizeIndex(IntermediateToIndex(Mu));

			return Interpolator->Interpolate(* this, Index, fmodf(Mu, 1.f));
		}

		template <typename TPathNode>
		float CPath<TPathNode>::BuildDistanceTable(float const Increment, SharedPtr<IInterpolator<TPathNode>> Interpolator)
		{
			if (! Interpolator)
				Interpolator = DefaultInterpolator;

			if (! Interpolator)
				return 0.f;

			DistanceTable.clear();
			// Store the increment at which this table was built
			MuIncrement = Increment;

			float const Max = static_cast<float>(Looping ? Nodes.size() : Nodes.size() - 1);
			TPathNode Last = Interpolator->Interpolate(* this, 0, 0.f);
			DistanceTable.push_back(0.f);

			for (float Mu = Increment;; Mu += Increment)
			{
				if (Mu > Max)
				{
					TPathNode Current = Interpolator->Interpolate(* this, SanitizeIndex(IntermediateToIndex(Max)), fmodf(Max, 1.f));
					DistanceTable.push_back((Current - Last).GetLength() + (DistanceTable.size() ? DistanceTable.back() : 0.f));
					break;
				}

				TPathNode Current = Interpolator->Interpolate(* this, SanitizeIndex(IntermediateToIndex(Mu)), fmodf(Mu, 1.f));
				DistanceTable.push_back((Current - Last).GetLength() + (DistanceTable.size() ? DistanceTable.back() : 0.f));
				Last = Current;
			}

			return DistanceTable.back();
		}


		template <typename TPathNode>
		float CPath<TPathNode>::GetIntermediateFromDistance(float const Distance, SharedPtr<IInterpolator<TPathNode>> Interpolator)
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

		template <typename TPathNode>
		TPathNode CPath<TPathNode>::GetNodeFromDistance(float const Distance, SharedPtr<IInterpolator<TPathNode>> Interpolator)
		{
			if (! Interpolator)
				Interpolator = DefaultInterpolator;

			if (! Interpolator)
				return TPathNode();

			float const Mu = GetIntermediateFromDistance(Distance);
			int const Index = SanitizeIndex(IntermediateToIndex(Mu));

			return Interpolator->Interpolate(* this, Index, fmodf(Mu, 1.f));
		}

		template <typename TPathNode>
		float CPath<TPathNode>::GetTotalPathLength()
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
